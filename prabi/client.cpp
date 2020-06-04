#include "client.h"

SOCKET ClientConnectToServer(const char* host, int port)
{
	return SOCKET();
}

bool ClientVerifyServer(SOCKET server)
{
	char buf[4];
	SendData(server, "RABI", 4);
	ReciveData(server, buf, 4);
	if (memcmp(buf, "JUMP", 4) != 0)
		return false;
	return true;
}

void ClientDeamon(SOCKET client, const VirtualTarget& vt)
{
	while (true)
		;

}
