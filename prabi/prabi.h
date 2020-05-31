#pragma once
#ifndef _PRABI_HEADER_
#define _PRABI_HEADER_
#include "pack.h"
#include "network.h"
#include "os.h"

void PrabiStartServerDeamon(SOCKET server);
void PrabiStartClientDeamon(SOCKET client);

//############# Client Side Functions ##################

// server accepted a new connection
int PrabiClientConnectionEstablished(SOCKET server);


//############# Server Side Functions ##################

// server accepted a new connection
int PrabiServerConnectionEstablished(SOCKET client);
void ThisIsNotAHTTPServer(SOCKET client);

#endif // _PRABI_HEADER_

