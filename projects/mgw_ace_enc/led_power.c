//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   26 january 2015                                     &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - handles LED "power"                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - This function is called by the timer 1 interrupt  &&&
//&&&                     every second                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Hystory     :                                                       &&&
//&&&   1.0 - 26/01/2015 - PBL - First release                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "common.h"
#include "io_control.h"

extern CONTEXT g;

void toggle_power_led()
{
    // Pattern definition:
    // 0 = LED OFF
    // 1 = Starting
    // 2 = Updating
    // 3 = Power Good default
    // 4 = Temperature default
    // 5 = Fan default
    // 6 = Input Voltage default
    // 7 = LED ON

    static u8 cnt = 0;

    switch (g.led_pattern)
    {
        case LED_PATTERN_OFF :
            PIN_LED_POWER = 0;
            break;

        case LED_PATTERN_STARTING :    // 1s=ON 1s=OFF
            PIN_LED_POWER = !PIN_LED_POWER;
            break;

        case LED_PATTERN_UPDATING :    // 3s=ON 1s=OFF
            if (cnt == 0 || cnt == 1 || cnt == 3 || cnt == 4){
                PIN_LED_POWER = 1;
                cnt++;
            }else if (cnt == 13){
                PIN_LED_POWER = 0;
                cnt = 0;
            }else{
                PIN_LED_POWER = 0;
                cnt++;
            }
            break;

        case LED_PATTERN_PWR_DEFAULT :    // 3s=ON 1s=OFF 1s=ON 1s=OFF
            if (cnt == 0 || cnt == 1 || cnt == 2 || cnt == 4){
                PIN_LED_POWER = 1;
                cnt++;
            }else if (cnt == 3){
                PIN_LED_POWER = 0;
                cnt++;
            }else{
                PIN_LED_POWER = 0;
                cnt=0;
            }
            break;

        case LED_PATTERN_TEMP_DEFAULT :    // 3s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF
            if (cnt == 0 || cnt == 1 || cnt == 2 || cnt == 4 || cnt == 6){
                PIN_LED_POWER = 1;
                cnt++;
            }else if (cnt == 3 || cnt == 5){
                PIN_LED_POWER = 0;
                cnt++;
            }else{
                PIN_LED_POWER = 0;
                cnt=0;
            }
            break;

        case LED_PATTERN_FAN_DEFAULT :    // 3s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF
            if (cnt == 0 || cnt == 1 || cnt == 2 || cnt == 4 || cnt == 6 || cnt == 8){
                PIN_LED_POWER = 1;
                cnt++;
            }else if (cnt == 3 || cnt == 5 || cnt == 7){
                PIN_LED_POWER = 0;
                cnt++;
            }else{
                PIN_LED_POWER = 0;
                cnt=0;
            }
            break;

        case LED_PATTERN_PWR_IN_DEFAULT :    // 3s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF 1s=ON 1s=OFF
            if (cnt == 0 || cnt == 1 || cnt == 2 || cnt == 4 || cnt == 6 || cnt == 8 || cnt == 10){
                PIN_LED_POWER = 1;
                cnt++;
            }else if (cnt == 3 || cnt == 5 || cnt == 7 || cnt == 9){
                PIN_LED_POWER = 0;
                cnt++;
            }else{
                PIN_LED_POWER = 0;
                cnt=0;
            }
            break;

        case LED_PATTERN_ON :
            PIN_LED_POWER = 1;
            break;

        case LED_PATTERN_POWERING_DOWN :
            PIN_LED_POWER = !PIN_LED_POWER;
            break;

        default :
            break;
    }

}
