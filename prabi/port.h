#pragma once
#ifndef _VPORT_HEADER_
#define _VPORT_HEADER_
#include "network.h"

class VirtualPort 
{
public:
	VirtualPort();
	~VirtualPort();
private:
	const char* addr;
	uint16_t port;
	SOCKET server;
};


#endif // !_VPORT_HEADER_
