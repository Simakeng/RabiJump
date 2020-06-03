#pragma once
#include "network.h"
#include "target.h"

SOCKET ClientConnectToServer(const char* host, int port);

void ClientDeamon(SOCKET client, const VirtualTarget& vt);
