#include "io.h"
#include "types.h"


#define PPS_IN_SCL1             0x13
#define PPS_IN_SDA1             0x14

#define PPS_OUT_CCP1            18
#define PPS_OUT_UART1_TX        19
#define PPS_OUT_I2C1_SCL        33
#define PPS_OUT_I2C1_SDA        34

void pin_manager_init(void)
{
    //-----------------------------------------------------------------------------
    /* set directions */
    set_port_A_input(BIT_3 | BIT_2);            // switches
    set_port_B_input(0);
    set_port_C_input(BIT_7 | BIT_4 | BIT_3);    // uart_rx, i2c_scl, i2c_sda

#if defined (_18F252)

    //-----------------------------------------------------------------------------
    /* select analog / digital GPIO */
    ADCON1 = 0x0F;

#endif

#if defined (_18F26K42)

    //-----------------------------------------------------------------------------
    /* select analog / digital GPIO */
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    //-----------------------------------------------------------------------------
    /* Configure RC3, RC4 as OD */
    ODCONA = 0;
    ODCONB = 0;
    ODCONC = 0;
    ODCONCbits.ODCC3 = 1;   /* I2C1 SCL */
    ODCONCbits.ODCC4 = 1;   /* I2C1 SDA */

    //-----------------------------------------------------------------------------
    //*I2C specific thresholds */
    RC3I2Cbits.TH = 1; 
    RC4I2Cbits.TH = 1; 

    //-----------------------------------------------------------------------------
    /* No slew rate limiting */
    SLRCONCbits.SLRC3 = 0; 
    SLRCONCbits.SLRC4 = 0;

    //-----------------------------------------------------------------------------
    // PPS configuration
    bool_t state = (unsigned char)GIE;
    GIE = 0;
    PPSLOCK = 0x55; // Unlock sequence
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    /* UART */
    RC6PPS = PPS_OUT_UART1_TX;

    /* CCP */
    // RC1PPS = PPS_CCP1;

    /* I2C */
    RC3PPS = PPS_OUT_I2C1_SCL;
    RC4PPS = PPS_OUT_I2C1_SDA;
    I2C1SDAPPSbits.I2C1SDAPPS = PPS_IN_SDA1;
    I2C1SCLPPSbits.I2C1SCLPPS = PPS_IN_SCL1;

    //-----------------------------------------------------------------------------
    PPSLOCK = 0x55; // Lock sequence
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;

#endif

}
