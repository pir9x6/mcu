/*********************************************************************
 *
 *                  AutoIP Defs for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        AutoIP.h
 * Dependencies:    
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 ********************************************************************/

#ifndef __AUTOIP_H
#define __AUTOIP_H

// AutoIP State Machine
typedef enum _SM_AUTOIP
{
    SM_AUTOIP_DISABLED = 0,
    SM_AUTOIP_INIT_RNG,
    SM_AUTOIP_CHECK_ADDRESS,
    SM_AUTOIP_SETUP_MESSAGE,
    SM_AUTOIP_GRATUITOUS_ARP1,
    SM_AUTOIP_GRATUITOUS_ARP2,
    SM_AUTOIP_GRATUITOUS_ARP3,
    SM_AUTOIP_DELAY,
    SM_AUTOIP_RATE_LIMIT_SET,
    SM_AUTOIP_RATE_LIMIT_WAIT,
    SM_AUTOIP_CONFIGURED,
    SM_AUTOIP_DEFEND
} SM_AUTOIP;


// Function prototypes
void AutoIPInit(u8 vInterface);
void AutoIPTasks(void);
void AutoIPConflict(u8 vInterface);
BOOL AutoIPIsConfigured(u8 vInterface);
BOOL AutoIPConfigIsInProgress (u8 vInterface);
BOOL AutoIPIsDisabled(u8 vInterface);
void AutoIPDisable(u8 vInterface);
void AutoIPEnable(u8 vInterface);


#endif
