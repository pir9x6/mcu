
#include "dht11.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Envoi du Start -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void DHT11_start ()
{
    DHT_TRIS = 0;   // DHT pin as an output
    DHT_PIN = 1;    // start 
    delay_us (10);
    DHT_PIN = 0;    // low pulse
    delay_ms (25);  // during at least 18 ms
    DHT_PIN = 1;
    delay_us (30);  // wait during 20 to 40 us
    DHT_TRIS = 1;   // DHT pin as an input
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------- Attendre la réponse du DHT11 après l'envoi du start -------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void DHT11_check_response ()
{
    //while (DHT_PIN);    // attendre que le signal repasse Ã  0
    while (!DHT_PIN);    // attendre que le signal repasse Ã  1
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------- Lecture des 40 octets provenant du DHT11 -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void DHT11_read ()
{
    
}

