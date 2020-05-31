#include "prabi.h"

#include <thread>

bool stop = false;

void PrabiStartServerDeamon(SOCKET server)
{
	using namespace std;
	while (true)
	{
		sockaddr_in clientAddr;
		int _len = sizeof(clientAddr);
		SOCKET sclient = accept(server, (SOCKADDR*)&clientAddr, &_len);
		thread clientThread = thread([=](SOCKET sclient, sockaddr_in clientAddr)
			{
				try
				{
					char strAddr[INET_ADDRSTRLEN];
					inet_ntop(AF_INET, &(clientAddr.sin_addr), strAddr, INET_ADDRSTRLEN);

					PrabiServerConnectionEstablished(sclient);

					printf("Rabi Client Connected! %s\n", strAddr);

					while (!stop)
					{


					}
					return;
				}
				catch (const std::exception& e)
				{
					printf("Server Error occured: %s\n", e.what());
				}
				catch (...) 
				{
					printf("Server Error occured: Unkwon\n");
				}

				try
				{
					closesocket(sclient);
				}
				catch (...)
				{
					return;
				}

			}, sclient, clientAddr);
		clientThread.detach();
	}
}

void PrabiStartClientDeamon(SOCKET server)
{
	PrabiClientConnectionEstablished(server);
	while (!stop)
	{

	}
}

int PrabiClientConnectionEstablished(SOCKET server) 
{
	SendData(server, "RABI", 4);
	char buf[4];
	ReciveData(server, buf, 4);
	if (memcmp(buf, "JUMP", 4) != 0) 
		throw std::exception("Server is not a RabiJump Server.");

	return 0;
}

int PrabiServerConnectionEstablished(SOCKET client)
{
	char buf[4];
	ReciveData(client, buf, 4);
	if (memcmp(buf, "RABI", 4) != 0) 
	{
		if (memcmp(buf, "GET ", 4) == 0)
		{
			ThisIsNotAHTTPServer(client);
			throw std::exception("Client Sends a HTTP Request");
		}
		throw std::exception("Error info header");
	}
	SendData(client, "JUMP", 4);

	return 0;
}

void ThisIsNotAHTTPServer(SOCKET client)
{
	const char* resps[] =
	{
		"HTTP/1.1 406 Not Acceptable\r\n",
		"Upgrade: RabiJump\r\n",
		"Connection: Close\r\n",
		"Content-Type: text/HTML\r\n",
		"\r\n",
		"<title> This is not a HTTP Server </title>",
		"<h1> This is not a HTTP Server </h1>",
		"<p> This is a RabiJump Server </p>",
		"<p> For more infomation, see <a href=\"https://github.com/Simakeng/RabiJump\">Simakeng/RabiJump</a> </p>" };
	char dummy[4];
	while (memcmp(dummy, "\r\n\r\n", 4) != 0) 
	{
		for (int i = 0; i < 3; i++)
			dummy[i] = dummy[i + 1];
		recv(client, dummy + 3, 1, 0);
	}
	for(auto resp : resps)
		send(client, resp, strlen(resp), 0);
	
}
