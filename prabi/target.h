#pragma once

#include "session.h"
#include "network.h"
#include "queue.h"
#include "pack.h"

#include <cstdint>
#include <unordered_map>

class VirtualTarget
{
public:
	VirtualTarget(const char* ipaddr, uint16_t port);
	~VirtualTarget();

private:
	const char* addr;
	const uint16_t port;

	std::unordered_map<uint32_t, Session> sessions;
public:
	uint32_t CreateSession();
	// forward a data packet to target;
	void Forward(uint32_t sid, const RawDataPack& packet);

};

