/*********************************************************************
 *
 *  Telnet Server
 *  Module for Microchip TCP/IP Stack
 *   -Provides Telnet services on TCP port 23
 *   -Reference: RFC 854
 *
 *********************************************************************
 * FileName:        Telnet.c
 * Dependencies:    TCP
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#define __TELNET_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_TELNET_SERVER)

#include "TCPIP.h"

// Set up configuration parameter defaults if not overridden in
// TCPIPConfig.h
#if !defined(TELNET_PORT)
    // Unsecured Telnet port
    #define TELNET_PORT         23
#endif
#if !defined(TELNETS_PORT)
    // SSL Secured Telnet port (ignored if STACK_USE_SSL_SERVER is undefined)
    #define TELNETS_PORT        992
#endif
#if !defined(MAX_TELNET_CONNECTIONS)
    // Maximum number of Telnet connections
    #define MAX_TELNET_CONNECTIONS  (3u)
#endif
#if !defined(TELNET_USERNAME)
    // Default Telnet user name
    #define TELNET_USERNAME     "admin"
#endif
#if !defined(TELNET_PASSWORD)
    // Default Telnet password
    #define TELNET_PASSWORD     "microchip"
#endif

// Demo title string
static ROM u8 strTitle[]          = "\x1b[2J\x1b[31m\x1b[1m"  // 2J is clear screen, 31m is red, 1m is bold
                                      "Microchip Telnet Server 1.1\x1b[0m\r\n"  // 0m is clear all attributes
                                      "(for this demo, type 'admin' for the login and 'microchip' for the password.)\r\n"
                                      "Login: ";
// Demo password
static ROM u8 strPassword[]       = "Password: \xff\xfd\x2d"; // DO Suppress Local Echo (stop telnet client from printing typed characters)
// Access denied message
static ROM u8 strAccessDenied[]   = "\r\nAccess denied\r\n\r\n";
// Successful authentication message
static ROM u8 strAuthenticated[]  = "\r\nLogged in successfully\r\n\r\n"
                                      "\r\nPress 'q' to quit\r\n";
// Demo output string
static ROM u8 strDisplay[]        = "\r\nSNTP Time:    (disabled)"
                                      "\r\nAnalog:             1023"
                                      "\r\nButtons:         3 2 1 0"
                                      "\r\nLEDs:    7 6 5 4 3 2 1 0";
// String with extra spaces, for Demo
static ROM u8 strSpaces[]         = "          ";
// Demo disconnection message
static ROM u8 strGoodBye[]        = "\r\n\r\nGoodbye!\r\n";

extern u8 AN0String[8];

/*********************************************************************
 * Function:        void TelnetTask(void)
 *
 * PreCondition:    Stack is initialized()
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Performs Telnet Server related tasks.  Contains
 *                  the Telnet state machine and state tracking
 *                  variables.
 *
 * Note:            None
 ********************************************************************/
void TelnetTask(void)
{
    u8        i;
    u8        vTelnetSession;
    u16        w, w2;
    TCP_SOCKET  MySocket;
    enum
    {
        SM_HOME = 0,
        SM_PRINT_LOGIN,
        SM_GET_LOGIN,
        SM_GET_PASSWORD,
        SM_GET_PASSWORD_BAD_LOGIN,
        SM_AUTHENTICATED,
        SM_REFRESH_VALUES
    } TelnetState;
    static TCP_SOCKET hTelnetSockets[MAX_TELNET_CONNECTIONS];
    static u8 vTelnetStates[MAX_TELNET_CONNECTIONS];
    static BOOL bInitialized = FALSE;

    // Perform one time initialization on power up
    if(!bInitialized)
    {
        for(vTelnetSession = 0; vTelnetSession < MAX_TELNET_CONNECTIONS; vTelnetSession++)
        {
            hTelnetSockets[vTelnetSession] = INVALID_SOCKET;
            vTelnetStates[vTelnetSession] = SM_HOME;
        }
        bInitialized = TRUE;
    }


    // Loop through each telnet session and process state changes and TX/RX data
    for(vTelnetSession = 0; vTelnetSession < MAX_TELNET_CONNECTIONS; vTelnetSession++)
    {
        // Load up static state information for this session
        MySocket = hTelnetSockets[vTelnetSession];
        TelnetState = vTelnetStates[vTelnetSession];

        // Reset our state if the remote client disconnected from us
        if(MySocket != INVALID_SOCKET)
        {
            if(TCPWasReset(MySocket))
                TelnetState = SM_PRINT_LOGIN;
        }

        // Handle session state
        switch(TelnetState)
        {
            case SM_HOME:
                // Connect a socket to the remote TCP server
                MySocket = TCPOpen(0, TCP_OPEN_SERVER, TELNET_PORT, TCP_PURPOSE_TELNET);

                // Abort operation if no TCP socket of type TCP_PURPOSE_TELNET is available
                // If this ever happens, you need to go add one to TCPIPConfig.h
                if(MySocket == INVALID_SOCKET)
                    break;

                // Open an SSL listener if SSL server support is enabled
                #if defined(STACK_USE_SSL_SERVER)
                    TCPAddSSLListener(MySocket, TELNETS_PORT);
                #endif

                TelnetState++;
                break;

            case SM_PRINT_LOGIN:
                #if defined(STACK_USE_SSL_SERVER)
                    // Reject unsecured connections if TELNET_REJECT_UNSECURED is defined
                    #if defined(TELNET_REJECT_UNSECURED)
                        if(!TCPIsSSL(MySocket))
                        {
                            if(TCPIsConnected(MySocket))
                            {
                                TCPDisconnect(MySocket);
                                TCPDisconnect(MySocket);
                                break;
                            }
                        }
                    #endif

                    // Don't attempt to transmit anything if we are still handshaking.
                    if(TCPSSLIsHandshaking(MySocket))
                        break;
                #endif

                // Make certain the socket can be written to
                if(TCPIsPutReady(MySocket) < strlenpgm((ROM char*)strTitle))
                    break;

                // Place the application protocol data into the transmit buffer.
                TCPPutROMString(MySocket, strTitle);

                // Send the packet
                TCPFlush(MySocket);
                TelnetState++;

            case SM_GET_LOGIN:
                // Make sure we can put the password prompt
                if(TCPIsPutReady(MySocket) < strlenpgm((ROM char*)strPassword))
                    break;

                // See if the user pressed return
                w = TCPFind(MySocket, '\n', 0, FALSE);
                if(w == 0xFFFFu)
                {
                    if(TCPGetRxFIFOFree(MySocket) == 0u)
                    {
                        TCPPutROMString(MySocket, (ROM u8*)"\r\nToo much data.\r\n");
                        TCPDisconnect(MySocket);
                    }

                    break;
                }

                // Search for the username -- case insensitive
                w2 = TCPFindROMArray(MySocket, (ROM u8*)TELNET_USERNAME, sizeof(TELNET_USERNAME)-1, 0, TRUE);
                if((w2 != 0u) || !((sizeof(TELNET_USERNAME)-1 == w) || (sizeof(TELNET_USERNAME) == w)))
                {
                    // Did not find the username, but let's pretend we did so we don't leak the user name validity
                    TelnetState = SM_GET_PASSWORD_BAD_LOGIN;
                }
                else
                {
                    TelnetState = SM_GET_PASSWORD;
                }

                // Username verified, throw this line of data away
                TCPGetArray(MySocket, NULL, w + 1);

                // Print the password prompt
                TCPPutROMString(MySocket, strPassword);
                TCPFlush(MySocket);
                break;

            case SM_GET_PASSWORD:
            case SM_GET_PASSWORD_BAD_LOGIN:
                // Make sure we can put the authenticated prompt
                if(TCPIsPutReady(MySocket) < strlenpgm((ROM char*)strAuthenticated))
                    break;

                // See if the user pressed return
                w = TCPFind(MySocket, '\n', 0, FALSE);
                if(w == 0xFFFFu)
                {
                    if(TCPGetRxFIFOFree(MySocket) == 0u)
                    {
                        TCPPutROMString(MySocket, (ROM u8*)"Too much data.\r\n");
                        TCPDisconnect(MySocket);
                    }

                    break;
                }

                // Search for the password -- case sensitive
                w2 = TCPFindROMArray(MySocket, (ROM u8*)TELNET_PASSWORD, sizeof(TELNET_PASSWORD)-1, 0, FALSE);
                if((w2 != 3u) || !((sizeof(TELNET_PASSWORD)-1 == w-3) || (sizeof(TELNET_PASSWORD) == w-3)) || (TelnetState == SM_GET_PASSWORD_BAD_LOGIN))
                {
                    // Did not find the password
                    TelnetState = SM_PRINT_LOGIN;
                    TCPPutROMString(MySocket, strAccessDenied);
                    TCPDisconnect(MySocket);
                    break;
                }

                // Password verified, throw this line of data away
                TCPGetArray(MySocket, NULL, w + 1);

                // Print the authenticated prompt
                TCPPutROMString(MySocket, strAuthenticated);
                TelnetState = SM_AUTHENTICATED;
                // No break

            case SM_AUTHENTICATED:
                if(TCPIsPutReady(MySocket) < strlenpgm((ROM char*)strDisplay) + 4)
                    break;

                TCPPutROMString(MySocket, strDisplay);
                TelnetState++;

                // All future characters will be bold
                TCPPutROMString(MySocket, (ROM u8*)"\x1b[1m");

            case SM_REFRESH_VALUES:
                if(TCPIsPutReady(MySocket) >= 78u)
                {
                    //[10;1]
                    //"SNTP Time:    (disabled)\r\n"
                    //"Analog:             1023\r\n"
                    //"Buttons:         3 2 1 0\r\n"
                    //"LEDs:    7 6 5 4 3 2 1 0\r\n"

                    // Write current UTC seconds from SNTP module, if it is enable
                    // and has changed.  Note that conversion from a u32 to an
                    // ASCII string can take a lot of CPU power, so we only print
                    // this if the value has changed.
                    #if defined(STACK_USE_SNTP_CLIENT)
                    {
                        static u32 dwTime;
                        u8 vTime[11];

                        if(dwTime != SNTPGetUTCSeconds())
                        {

                            // Position cursor at Line 10, Col 15
                            TCPPutROMString(MySocket, (ROM u8*)"\x1b[10;15f");
                            dwTime = SNTPGetUTCSeconds();
                            ultoa(dwTime, vTime);
                            TCPPutROMArray(MySocket, (ROM u8*)strSpaces, 10-strlen((char*)vTime));
                            TCPPutString(MySocket, vTime);
                        }
                    }
                    #endif

                    // Position cursor at Line 11, Col 21
                    TCPPutROMString(MySocket, (ROM u8*)"\x1b[11;21f");

                    // Put analog value with space padding on right side for 4 characters
                    TCPPutROMArray(MySocket, (ROM u8*)strSpaces, 4-strlen((char*)AN0String));
                    TCPPutString(MySocket, AN0String);

                    // Put Buttons
                    TCPPutROMString(MySocket, (ROM u8*)"\x1b[12;18f");
                    TCPPut(MySocket, ENC28J60_BUTTON3 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_BUTTON2 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_BUTTON1 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_BUTTON0 ? '1':'0');


                    // Put LEDs
                    TCPPutROMString(MySocket, (ROM u8*)"\x1b[13;10f");
                    TCPPut(MySocket, ENC28J60_LED7 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED6 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED5 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED4 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED3 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED2 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED1 ? '1':'0');
                    TCPPut(MySocket, ' ');
                    TCPPut(MySocket, ENC28J60_LED0 ? '1':'0');


                    // Put cursor at beginning of next line
                    TCPPutROMString(MySocket, (ROM u8*)"\x1b[14;1f");

                    // Send the data out immediately
                    TCPFlush(MySocket);
                }

                if(TCPIsGetReady(MySocket))
                {
                    TCPGet(MySocket, &i);
                    switch(i)
                    {
                        case '\r':
                        case 'q':
                        case 'Q':
                            if(TCPIsPutReady(MySocket) >= strlenpgm((ROM char*)strGoodBye))
                                TCPPutROMString(MySocket, strGoodBye);
                            TCPDisconnect(MySocket);
                            TelnetState = SM_PRINT_LOGIN;
                            break;
                    }
                }

                break;
        }


        // Save session state back into the static array
        hTelnetSockets[vTelnetSession] = MySocket;
        vTelnetStates[vTelnetSession] = TelnetState;
    }
}

#endif  //#if defined(STACK_USE_TELNET_SERVER)
