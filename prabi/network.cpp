#include "network.h"

void InitNetworkEnv()
{
#ifdef PLATFORM_WINDOWS
	WSADATA wsa;
	int startup = WSAStartup(MAKEWORD(2, 0), &wsa);
	if (startup != 0)
		abort();
#endif // PLATFORM_WINDOWS
}

void PrabiStartListen(const char* host, int port, int max_con = 10, int af = AF_INET)
{
	SOCKADDR_IN serveraddr{ 0 };
	serveraddr.sin_family = af;
	serveraddr.sin_port = htons(port);
	inet_pton(af, host, &serveraddr.sin_addr);

	SOCKET server = socket(af, SOCK_STREAM, IPPROTO_TCP);
	if (!server)abort();

	if (!bind(server, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
		abort();

	if (!listen(server, max_con))
		abort();

	while (true)
	{
		SOCKET client = accept(server, nullptr, nullptr);
		std::thread clientThread = std::thread([=]()
			{
				bool close = false;
				uint8_t buf[256]{ 0 };
				while (!close)
				{
					int len = recv(client, (char*)buf, 256, 0);
				}
			})
	}
}