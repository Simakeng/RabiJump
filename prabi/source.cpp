#include "prabi.h"

/**
 * Current goal:
 * 1. Enstablish connection from machine A and B
 * 2. machine A listen on 0.0.0.0:port and forword pass all packet to machine B:port
 * 3. machine B resend all packet from A to an ipaddress:port
 */

 /**

 # listen at 0.0.0.0:1045
 prabi -s 0.0.0.0:1045

 # connect to server and forword all connection from server to www.baidu.com:80
 prabi -p 0.0.0.0:1045 www.baidu.com:80

 */

int main(int argc, char* argv[])
{
	InitNetworkEnv();

	auto splt = strstr(argv[2], ":");
	auto port = atoi(splt + 1);
	auto addrl = splt - argv[2];
	auto ipaddr = new char[addrl + 1]{ 0 };
	memcpy(ipaddr, argv[2], addrl);
	// for test purpose
	try
	{
		if (strcmp(argv[1], "-s") == 0)
		{
			printf("starting server...\n");
			SOCKET server = StartServer(ipaddr, port);
			SOCKET target = ServerWaitingTarget(server);
			ServerDeamon(server, target);
		}
		else if (strcmp(argv[1], "-p") == 0)
		{
			printf("connecting...\n");
			SOCKET server = StartClient(ipaddr, port);
			ClientVerifyServer(server);

			splt = strstr(argv[3], ":");
			port = atoi(splt + 1);
			addrl = splt - argv[3];
			ipaddr = new char[addrl + 1]{ 0 };
			memcpy(ipaddr, argv[2], addrl);

			ClientDeamon(server, VirtualTarget(ipaddr, port));
			//PrabiStartClientDeamon(client);
		}
	}
	catch (const std::exception& e)
	{
		printf("Error occured: %s", e.what());
	}
	catch (...)
	{
		printf("Error occured: Unknown Error.");
	}
}