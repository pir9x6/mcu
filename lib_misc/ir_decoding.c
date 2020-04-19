//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   August 2015                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Decodes IR signal with the following protocol:    &&&
//&&&                   - NEC                                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   na                                                  &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Requirements:   ir_decoding.c & ir_decoding.h                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    02/08/2015    Creation                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "ir_decoding.h"

extern u16 ir_address;
extern u8 ir_command;
extern u8 ir_new_cmd;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- NEC decoding ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT ir_nec_decoding()
{
    u32 cnt = 0;
    u32 i = 0;
    u8 b = 0;
    u8 new_cmd = 0;
    u8 repeat = 0;
    static u8 cmd_inv = 0;
    const u8 N = 20;
    const u16 T = 1300; // threshold 1 / 0

    // wait for start (negative pulse)
    for (i = 0; i < 40000/N; i++){
        delay_us(N);
        cnt++;

        if (IR == 1){
            break;
        }
    }

    if (cnt >= 40000/N-1)
        return ERROR;

    cnt = 0;
    for (i = 0; i < 40000/N; i++){
        delay_us(N);
        cnt++;

        if (IR == 0){
            // New command
            if (cnt*N > 3000){
                new_cmd = 1;
                repeat = 0;
            // repeat last command
            }else if (cnt*N > 1900){
                new_cmd = 0;
                repeat = 1;
            // unknown
            }else{
                return UNKNOWN;
            }
            ir_new_cmd = 1;
            break;
        }
    }

    if (cnt >= 40000/N-1)
        return ERROR;

    if (new_cmd){
        ir_command = 0;
        cmd_inv = 0;
        ir_address = 0;
        // =======================================
        // get address
        for (b = 0; b < 16; b++){
            // low pulse
            cnt = 0;
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 1){
                    break;
                }
            }

            // high pulse
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 0){
                    if (cnt*N > T){
                        ir_address |= 1<<b;
                    }
                    break;
                }
            }
        }

        // =======================================
        // get command
        for (b = 0; b < 8; b++){
            // low pulse
            cnt = 0;
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 1){
                    break;
                }
            }

            // high pulse
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 0){
                    if (cnt*N > T){
                        ir_command |= 1<<b;
                    }
                    break;
                }
            }
        }

        // =======================================
        // get inverted command
        for (b = 0; b < 8; b++){
            // low pulse
            cnt = 0;
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 1){
                    break;
                }
            }

            // high pulse
            for (i = 0; i < 4000/N; i++){
                delay_us(N);
                cnt++;

                if (IR == 0){
                    if (cnt*N > T){
                        cmd_inv |= 1<<b;
                    }
                    break;
                }
            }
        }
    }

    if (new_cmd){
        printf("New Command: ");
    }else if (repeat){
        printf("Repeat Command: ");
    }

//    printf("Address:     0x%04X \n", ir_address);
//    printf("Command:     0x%02X \n", ir_command);
//    printf("Command Inv: 0x%02X \n", cmd_inv);

    // filtered following pulses
    delay_ms (200);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- RC5 decoding ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT ir_rc5_decoding ()
{

    return SUCCESS;
}
