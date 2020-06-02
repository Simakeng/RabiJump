#pragma once
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

	struct VTSession
	{
		SOCKET remote;
		uint32_t sid;
		atomic_queue<RawDataPack> packetQueue;
		bool operator==(const VTSession& r)const { return this->remote == r.remote; }
	};

	std::unordered_map<uint32_t, VTSession> sessions;
public:
	uint32_t CreateSession();
	// forward a data packet to target;
	void Forward(uint32_t sid, const RawDataPack& packet);

	friend struct std::hash<VirtualTarget::VTSession>;
};

namespace std
{
	template<>
	struct hash<VirtualTarget::VTSession>
	{
		std::size_t operator() (const VirtualTarget::VTSession& t) { return t.sid; }
	};
}