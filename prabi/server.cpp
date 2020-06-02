#include "server.h"

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
		
		if (TargetConnectionAccepted(target))
			break;

		closesocket(target);
		target = NULL;
	}
	return target;
}

void ServerDeamon(SOCKET server, SOCKET target)
{

}
