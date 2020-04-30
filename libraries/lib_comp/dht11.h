#pragma once

#include "types.h"

//------------------------------ Envoi du Start -------------------------------
void dht11_start ();

//----------- Attendre la réponse du DHT11 aprés l'envoi du start -------------
void dht11_check_response ();

//---------------- Lecture des 40 octets provenant du DHT11 -------------------
void dht11_read ();

