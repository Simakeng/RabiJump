#pragma once
#ifndef _NETWORK_HEADER_
#define _NETWORK_HEADER_
#include "os.h"
struct Session
{
	SOCKET sclient;
	uint32_t sessionID;
};

void InitNetworkEnv();

void PrabiStartListen(const char* host, int port);
void PrabiStartConnecting(const char* host, int port);

void StartListen(int port);

#endif // _NETWORK_HEADER_
