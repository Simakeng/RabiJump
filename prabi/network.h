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
SOCKET PrabiStartServer(const char* host, int port, int max_con = 10);
SOCKET prabiStartClient(const char* target, int port);

void ReciveData(SOCKET s, void* buffer, size_t size);
#endif // _NETWORK_HEADER_
