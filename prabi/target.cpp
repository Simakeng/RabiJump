#include "target.h"
#include "network.h"
#include <string.h>
#include <random>
VirtualTarget::VirtualTarget(const char* ipaddr, uint16_t port)
	:addr(nullptr),
	port(port)
{
	auto addr = new char[strlen(ipaddr) + 1];
	strcpy(addr, ipaddr);
	this->addr = addr;
}

VirtualTarget::~VirtualTarget()
{
	delete[] addr;
}

uint32_t VirtualTarget::CreateSession()
{
	static std::mt19937 rnd(time(nullptr));
	auto sid = rnd();
	while (sid != 0 and sessions.find(sid) != sessions.end())
		sid = rnd();

	SOCKET client = StartClient(this->addr, this->port);
	if (client == NULL)
		return 0;

	sessions[sid] = Session{ sid,client };
	return sid;
}
