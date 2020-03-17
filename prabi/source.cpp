#include "prabi.h"
/**
 * Current Gole:
 * 1. Enstablish connection from machine A and B
 * 2. machine A listen on port_1 and forword pass all packet to machine B
 * 3. machine B resend all packet from A to an ipaddress:port
 */
int main(int argc, char* argv[])
{
    InitNetworkEnv();
	// argv[0] : cwd
	// argv[1] : listen port
	// argv[2] : target port

	int a;
}