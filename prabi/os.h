#pragma once
#ifndef _OS_HEADER
#define _OS_HEADER
#ifdef _MSVC_LANG
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <cstdint>
#include <thread>
#ifdef _WIN32

#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define PLATFORM_WINDOWS
#endif // _WIN32

#endif // _OS_HEADER
