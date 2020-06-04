#include "network.h"
#include "errors.h"
#include "config.h"

#include <exception>
#include <future>

void InitNetworkEnv()
{
#ifdef PLATFORM_WINDOWS
	WSADATA wsa;
	int startup = WSAStartup(MAKEWORD(2, 0), &wsa);
	if (startup != 0)
		abort();
#endif // PLATFORM_WINDOWS
}

const auto AF = AF_INET;

SOCKET StartServer(const char* host, int port, int max_con)
{
	SOCKADDR_IN serveraddr{ 0 };
	serveraddr.sin_family = AF;
	serveraddr.sin_port = htons(port);
	inet_pton(AF, host, &serveraddr.sin_addr);

	SOCKET server = socket(AF, SOCK_STREAM, IPPROTO_TCP);
	if (!server)
		throw std::exception(MAKE_ERRNO("Failed on create socket!"));

	if (bind(server, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
		throw std::exception(MAKE_ERRNO("Failed on bind Prabi server address!"));

	if (listen(server, max_con))
		throw std::exception(MAKE_ERRNO("Failed on listen Prabi server address!"));

	return server;
}

SOCKET StartClient(const char* target, int port)
{
	SOCKADDR_IN serveraddr{ 0 };
	serveraddr.sin_family = AF;
	serveraddr.sin_port = htons(port);
	inet_pton(AF, target, &serveraddr.sin_addr);

	SOCKET client = socket(AF, SOCK_STREAM, IPPROTO_TCP);
	if (connect(client, (sockaddr*)&serveraddr, sizeof(sockaddr)))
		throw std::exception(MAKE_ERRNO("Failed on connect to Prabi server address!"));

	return client;
}
void SendData(SOCKET s,const void* buffer, size_t size)
{
	const auto buf = reinterpret_cast<const char*>(buffer);
	auto bs = send(s, buf, size, 0);
	if (bs == -1)
		throw MAKE_ERRNO("Error when send data to remote.");
	if(bs!= size)
		throw std::exception("Error when send data to remote. - time out");
}

void ReciveData(SOCKET s, void* buffer, size_t size)
{
	size_t dataRecvd = 0;
	auto buf = reinterpret_cast<char*>(buffer);
	while (dataRecvd < size)
	{
		size_t cc = recv(s, buf, size - dataRecvd, 0);
		switch (cc)
		{
		case -1:throw MAKE_ERRNO("Error when recive data from remote.");
		case 0:throw std::exception("Error when recive data from remote.- End of stream!");
		}
		dataRecvd += cc;
	}
	return;
}


