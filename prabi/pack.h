#pragma once
#ifndef _PACK_HEADER_
#define _PACK_HEADER_
#include "os.h"
#include "network.h"
class RabiDataPack
{
public:
	~RabiDataPack();
private:
	uint32_t packetType;
	uint32_t sessionID;
	uint32_t packetLength;
	std::shared_ptr<uint8_t> packetData;
	
	friend RabiDataPack RecivePacket(SOCKET remote);
	friend void SendPacket(const RabiDataPack& packet, SOCKET target);
public:
	inline uint32_t sid() { return sessionID; }
	inline uint32_t size() { return packetLength; }
	inline uint8_t* data() { return &packetData.operator*(); }
};


struct RawDataPack 
{
	uint8_t* data;
	size_t len;
};


// Send packet to target.
void SendPacket(const RabiDataPack& packet, SOCKET target);
RabiDataPack RecivePacket(SOCKET remote);

#endif // _PACK_HEADER_

