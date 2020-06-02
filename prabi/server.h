#pragma once
#include "network.h"

SOCKET ServerWaitingTarget(SOCKET s);

void ServerDeamon(SOCKET server, SOCKET target);