/*********************************************************************
 *
 *                  UDP Module Defs for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        UDP.h
 * Dependencies:    StackTsk.h
 *                  MAC.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#ifndef __UDP_H
#define __UDP_H

// Stores a UDP Port Number
typedef u16 UDP_PORT;

// Provides a handle to a UDP Socket
typedef u8 UDP_SOCKET;

// Stores information about a current UDP socket
typedef struct
{
    NODE_INFO   remoteNode;		// IP and MAC of remote node
    UDP_PORT    remotePort;		// Remote node's UDP port number
    UDP_PORT    localPort;		// Local UDP port number, or INVALID_UDP_PORT when free
} UDP_SOCKET_INFO;


#define INVALID_UDP_SOCKET      (0xffu)		// Indicates a UDP socket that is not valid
#define INVALID_UDP_PORT        (0ul)		// Indicates a UDP port that is not valid

/****************************************************************************
  Section:
	External Global Variables
  ***************************************************************************/
#if !defined(__UDP_C)
    extern UDP_SOCKET activeUDPSocket;
    extern UDP_SOCKET_INFO  UDPSocketInfo[MAX_UDP_SOCKETS];
	extern u16 UDPTxCount;
	extern u16 UDPRxCount;
#endif

// Stores the header of a UDP packet
typedef struct
{
    UDP_PORT    SourcePort;				// Source UDP port
    UDP_PORT    DestinationPort;		// Destination UDP port
    u16        Length;					// Length of data
    u16        Checksum;				// UDP checksum of the data
} UDP_HEADER;

/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/
void UDPInit(void);
void UDPTask(void);

UDP_SOCKET UDPOpen(UDP_PORT localPort, NODE_INFO *remoteNode, UDP_PORT remotePort);
void UDPClose(UDP_SOCKET s);
BOOL UDPProcess(NODE_INFO *remoteNode, IP_ADDR *localIP, u16 len);

void UDPSetTxBuffer(u16 wOffset);
void UDPSetRxBuffer(u16 wOffset);
u16 UDPIsPutReady(UDP_SOCKET s);
BOOL UDPPut(u8 v);
u16 UDPPutArray(u8 *cData, u16 wDataLen);
u8* UDPPutString(u8 *strData);
void UDPFlush(void);

// ROM function variants for PIC18
#if defined(__18CXX)
	u16 UDPPutROMArray(ROM u8 *cData, u16 wDataLen);
	ROM u8* UDPPutROMString(ROM u8 *strData);
#else
	#define UDPPutROMArray(a,b)	UDPPutArray((u8*)a,b)
	#define UDPPutROMString(a)	UDPPutString((u8*)a)
#endif

u16 UDPIsGetReady(UDP_SOCKET s);
BOOL UDPGet(u8 *v);
u16 UDPGetArray(u8 *cData, u16 wDataLen);
void UDPDiscard(void);

#endif
