/*******************************************************************************
  System Config Performance function implementation
  Company:
    Microchip Technology Inc.
  File Name:
    config_performance.c
  Summary:
    Contains a non-ISP implementation of legacy SYSTEMConfigPerformance
    function
  Description:
    This file contains a non-ISP implementation of the legacy
    SYSTEMConfigPerformance function. The file is self contained and does
    not require inclusion of legacy plib.h file.
*******************************************************************************/

#include "hardware_profile.h"
#include "config_performance.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __attribute__ ((nomips16)) CheKseg0CacheOn()
{
    register unsigned long tmp;
    asm("mfc0 %0,$16,0" :  "=r"(tmp));
    tmp = (tmp & ~7) | 3;
    asm("mtc0 %0,$16,0" :: "r" (tmp));
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int DmaSuspend(void)
{
    int suspSt;
    if (!(suspSt = DMACONbits.SUSPEND))
    {
        DMACONSET =_DMACON_SUSPEND_MASK;    // suspend
        while ((DMACONbits.DMABUSY));       // wait to be actually suspended
    }
    return suspSt;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void DmaResume(int susp)
{
    if(susp)
    {
        DmaSuspend();
    }
    else
    {
        DMACONCLR = _DMACON_SUSPEND_MASK;     // resume DMA activity
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
unsigned int INTDisableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("di    %0" : "=r"(status));

    return status;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void INTRestoreInterrupts(unsigned int status)
{
    if(status & 0x00000001)
        asm volatile("ei");
    else
        asm volatile("di");
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void OSCSetPBDIV(unsigned int oscPbDiv)
{
    unsigned int dma_status;
    unsigned int int_status;
    __OSCCONbits_t oscBits;

    mSYSTEMUnlock(int_status, dma_status);

    oscBits.w = OSCCON;       // read to be in sync. flush any pending write
    oscBits.PBDIV = 0;
    oscBits.w |= oscPbDiv;
    OSCCON = oscBits.w;       // write back
    oscBits.w = OSCCON;       // make sure the write occurred before returning from this function

    mSYSTEMLock(int_status, dma_status);
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
unsigned int SYSTEMConfigPB(unsigned int sys_clock)
{
    unsigned int pb_div;
    unsigned int pb_clock;

    pb_clock = sys_clock;

    if(sys_clock > PB_BUS_MAX_FREQ_HZ)
    {
        pb_div=OSC_PB_DIV_2;
        pb_clock >>= 1;
    }
    else
    {
        pb_div=OSC_PB_DIV_1;
    }

    OSCSetPBDIV(pb_div);

    return pb_clock;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
unsigned int SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock)
{
#ifdef _PCACHE
    unsigned int wait_states;
#endif
    unsigned int pb_clock;
    unsigned int int_status;

    pb_clock = SYSTEMConfigPB(sys_clock);


    // set the flash wait states based on 1 wait state
    // for every 20 MHz
#ifdef _PCACHE
    wait_states = 0;

    while(sys_clock > FLASH_SPEED_HZ)
    {
        wait_states++;
        sys_clock -= FLASH_SPEED_HZ;
    }

    int_status=INTDisableInterrupts();
    mCheConfigure(wait_states);
    INTRestoreInterrupts(int_status);

#endif

    return pb_clock;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)
{
    // set up the wait states
    unsigned int pb_clk;
#ifdef _PCACHE
    unsigned int cache_status;
#endif
    unsigned int int_status;

    pb_clk = SYSTEMConfigWaitStatesAndPB(sys_clock);

    int_status=INTDisableInterrupts();

    mBMXDisableDRMWaitState();

#ifdef _PCACHE
    cache_status = mCheGetCon();
    cache_status |= CHE_CONF_PF_ALL;
    mCheConfigure(cache_status);
    CheKseg0CacheOn();
#endif

    INTRestoreInterrupts(int_status);

    return pb_clk;

}



/*********************************************************************
  Function:
    unsigned int SYSTEMConfig(unsigned int sys_clock, unsigned int flags)

  Description:
    The function sets the PB divider, the Flash Wait states or the DRM wait states to the optimum value,
    based on the flags selected and on the frequency of the system clock.
    It also enables the cacheability for the K0 segment.

  PreCondition:
    None

  Parameters:
    sys_clock - system clock frequency in Hz
    flags -
        *    SYS_CFG_WAIT_STATES  - configure the flash wait states from the system clock
        *    SYS_CFG_PB_BUS       - configure the PB bus from the system clock
        *    SYS_CFG_PCACHE      - configure the pCache (if used)
        *    SYS_CFG_ALL          - configure all based on system clock

  Returns:
    the PB clock frequency in Hz

  Side Effects:
    Could change the wait state, pb clock and turn on the pre-fetch buffer and cache. Sets the RAM
    wait state to 0.


  Remarks:
    The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
    Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.

  Example:
    <code>
    SYSTEMConfig(72000000, SYS_CFG_ALL);
    </code>
 ********************************************************************/
unsigned int system_config(unsigned int sys_clock, unsigned int flags)
{
    unsigned int pb_clk;
    unsigned int int_status;
#ifdef _PCACHE
    unsigned int cache_status;
#endif

    int_status = INTDisableInterrupts();

    mBMXDisableDRMWaitState();

    if (flags & SYS_CFG_WAIT_STATES)
    {
        SYSTEMConfigWaitStatesAndPB(sys_clock);
    }

    if (flags & SYS_CFG_PB_BUS)
    {
        SYSTEMConfigPB(sys_clock);
    }


#ifdef _PCACHE
    if (flags & SYS_CFG_PCACHE)
    {
        cache_status = mCheGetCon();
        cache_status |= CHE_CONF_PF_ALL;
        mCheConfigure(cache_status);
        CheKseg0CacheOn();
    }
#endif

    pb_clk = sys_clock;
    pb_clk >>= OSCCONbits.PBDIV;

    INTRestoreInterrupts(int_status);

    return pb_clk;

}
