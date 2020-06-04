#pragma once
#include "network.h"
#include "target.h"

SOCKET ClientConnectToServer(const char* host, int port);

bool ClientVerifyServer(SOCKET server);

void ClientDeamon(SOCKET client, const VirtualTarget& vt);
