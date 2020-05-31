#pragma once
#ifndef _PRABI_HEADER_
#define _PRABI_HEADER_
#include "pack.h"
#include "network.h"
#include "os.h"





//############# Client Side Functions ##################

// Become a client deamon process.
void PrabiStartClientDeamon(SOCKET client);

// Server accepted a new connection
int PrabiClientConnectionEstablished(SOCKET server);


//############# Server Side Functions ##################

// Become a server deamon process.
void PrabiStartServerDeamon(SOCKET server);

// Server accepted a new connection.
int PrabiServerConnectionEstablished(SOCKET client);
void ThisIsNotAHTTPServer(SOCKET client);

#endif // _PRABI_HEADER_

