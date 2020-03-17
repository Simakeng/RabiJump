#pragma once
#ifndef _OS_HEADER
#define _OS_HEADER
#include <cstdint>
#include <thread>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define PLATFORM_WINDOWS
#endif // _WIN32

#endif // _OS_HEADER
