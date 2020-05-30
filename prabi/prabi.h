#pragma once
#ifndef _PRABI_HEADER_
#define _PRABI_HEADER_
#include "pack.h"
#include "network.h"
#include "os.h"

void PrabiStartServerDeamon(SOCKET server);
void PrabiStartClientDeamon(SOCKET client);

//############# Server Side Functions ##################
int FirstConnect(SOCKET client);
void ThisIsNotAHTTPServer(SOCKET client);

#endif // _PRABI_HEADER_

