/*********************************************************************
 *
 *                  ARP Module Defs for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        ARP.h
 * Dependencies:    Stacktsk.h
 *                  MAC.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#ifndef __ARP_H
#define __ARP_H

#ifdef STACK_CLIENT_MODE
	void ARPInit(void);
#else
	#define ARPInit()
#endif

#define ARP_OPERATION_REQ       0x0001u		// Operation code indicating an ARP Request
#define ARP_OPERATION_RESP      0x0002u		// Operation code indicating an ARP Response

#define HW_ETHERNET             (0x0001u)	// ARP Hardware type as defined by IEEE 802.3
#define ARP_IP                  (0x0800u)	// ARP IP packet type as defined by IEEE 802.3


// ARP packet structure
typedef struct __attribute__((aligned(2), packed))
{
    u16        HardwareType;
    u16        Protocol;
    u8        MACAddrLen;
    u8        ProtocolLen;
    u16        Operation;
    MAC_ADDR    SenderMACAddr;
    IP_ADDR     SenderIPAddr;
    MAC_ADDR    TargetMACAddr;
    IP_ADDR     TargetIPAddr;
} ARP_PACKET;

BOOL ARPProcess(void);
void ARPResolve(IP_ADDR* IPAddr);
BOOL ARPIsResolved(IP_ADDR* IPAddr, MAC_ADDR* MACAddr);
void SwapARPPacket(ARP_PACKET* p);

#ifdef STACK_USE_ZEROCONF_LINK_LOCAL
	/* API specific Definitions */
	#define ARP_REQ       0x0001u		// Operation code indicating an ARP Request
	#define ARP_RESP      0x0002u		// Operation code indicating an ARP Response

	struct arp_app_callbacks {
    	BOOL used;
    	void (*ARPPkt_notify)(u32 SenderIPAddr, u32 TargetIPAddr, 
                          	MAC_ADDR* SenderMACAddr, MAC_ADDR* TargetMACAddr, u8 op_req);
	};
	CHAR ARPRegisterCallbacks(struct arp_app_callbacks *app);
	BOOL ARPDeRegisterCallbacks(CHAR id);
	BOOL ARPSendPkt(u32 SrcIPAddr, u32 DestIPAddr, u8 op_req );
#endif

#endif


