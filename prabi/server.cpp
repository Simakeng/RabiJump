#include <thread>
#include <unordered_map>

#include "server.h"
#include "config.h"
#include "session.h"

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
	for (auto resp : resps)
		send(client, resp, strlen(resp), 0);
}

int TargetConnectionAccepted(SOCKET client)
{
	char buf[4];
	ReciveData(client, buf, 4);
	if (memcmp(buf, "RABI", 4) != 0)
	{
		if (memcmp(buf, "GET ", 4) == 0)
		{
			ThisIsNotAHTTPServer(client);
			printf("Client Sends a HTTP Request\n");
			return -1;
		}
		printf("Error info header\n");
		return -1;
	}
	SendData(client, "JUMP", 4);

	return 0;
}

SOCKET ServerWaitingTarget(SOCKET s)
{
	SOCKET target = NULL;
	sockaddr addr;
	int addrLen = sizeof(sockaddr);
	while (target == NULL)
	{
		target = accept(s, &addr, &addrLen);

		if (TargetConnectionAccepted(target) == 0)
			break;

		closesocket(target);
		target = NULL;
	}
	return target;
}

Session ServerAllocateSession(SOCKET target)
{

}

void ServerDeamon(SOCKET server, SOCKET target)
{
	std::unordered_map<uint32_t, Session> sessions;

	auto targetReciveThread = std::thread([&target,&sessions]() mutable
		{
			auto packet = RecivePacket(target);
		});
	
	while (!stop)
	{
		sockaddr addr;
		int addrl = sizeof(sockaddr);
		SOCKET user = accept(server, &addr, &addrl);
		Session ns;
		// Try request target to allocate new session

		// obtain new session id

		// start forwarding process
	}
}