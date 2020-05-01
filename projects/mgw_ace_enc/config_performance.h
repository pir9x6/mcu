#ifndef _CONFIG_PERFORMANCE_H_
#define _CONFIG_PERFORMANCE_H_

#include "hardware_profile.h"

#define FLASH_SPEED_HZ          30000000 //Max Flash speed
#define PB_BUS_MAX_FREQ_HZ      80000000 //Max Peripheral bus speed

/*********************************************************************
 * SYSTEMConfig Flags
 *********************************************************************/
#define SYS_CFG_WAIT_STATES     0x00000001 //SYSTEMConfig wait states
#define SYS_CFG_PB_BUS          0x00000002 //SYSTEMConfig pb bus
#define SYS_CFG_PCACHE          0x00000004 //SYSTEMConfig cache
#define SYS_CFG_ALL             0xFFFFFFFF //SYSTEMConfig All

#define OSC_PB_DIV_2            (1 << _OSCCON_PBDIV_POSITION)
#define OSC_PB_DIV_1            (0 << _OSCCON_PBDIV_POSITION)

#define PB_BUS_MAX_FREQ_HZ      80000000
#define FLASH_SPEED_HZ          30000000

#define CHE_CONF_PF_ALL         (3 << _CHECON_PREFEN_POSITION)

#ifdef _DMAC
    #define mSYSTEMUnlock(intStat, dmaSusp) do{intStat=INTDisableInterrupts(); dmaSusp=DmaSuspend(); \
                        SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;}while(0)
#else
    #define mSYSTEMUnlock(intStat, dmaSusp) do{intStat=INTDisableInterrupts(); \
                        SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;}while(0)
#endif  // _DMAC

#ifdef _DMAC
    #define mSYSTEMLock(intStat, dmaSusp)   do{SYSKEY = 0x33333333; DmaResume(dmaSusp); INTRestoreInterrupts(intStat);}while(0)
#else
    #define mSYSTEMLock(intStat, dmaSusp)   do{SYSKEY = 0x33333333; INTRestoreInterrupts(intStat);}while(0)
#endif // _DMAC

#define mBMXDisableDRMWaitState()   (BMXCONCLR = _BMXCON_BMXWSDRM_MASK)

#define mCheGetCon() CHECON

#define mCheConfigure(val) (CHECON = (val))


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __attribute__ ((nomips16)) CheKseg0CacheOn();
int DmaSuspend(void);
void DmaResume(int susp);
unsigned int INTDisableInterrupts(void);
void INTRestoreInterrupts(unsigned int status);
void OSCSetPBDIV(unsigned int oscPbDiv);
unsigned int SYSTEMConfigPB(unsigned int sys_clock);
unsigned int SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock);
unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);
unsigned int system_config(unsigned int sys_clock, unsigned int flags);

#endif
