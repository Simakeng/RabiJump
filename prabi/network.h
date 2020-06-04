#pragma once
#ifndef _NETWORK_HEADER_
#define _NETWORK_HEADER_

#include "os.h"
#include "pack.h"
#include "queue.h"

void InitNetworkEnv();
SOCKET StartServer(const char* host, int port, int max_con = 10);
SOCKET StartClient(const char* target, int port);

void SendData(SOCKET s, const void* buffer, size_t size);
void ReciveData(SOCKET s, void* buffer, size_t size);


template<typename T>
void ExecuteWhenRecived(SOCKET target, const bool& stop, const T& func)
{
	auto forward_th = std::thread([&stop]()
		{
			while (!stop)
			{
				char buf[2048];
				int len = recv(target, buf, 2048, 0);
				func(len, buf);
			}
		});
	forward_th.detach();
}

#endif // _NETWORK_HEADER_
