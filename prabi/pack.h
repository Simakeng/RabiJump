#pragma once
#ifndef _PACK_HEADER_
#define _PACK_HEADER_
#include "os.h"

struct RabiDataPack
{
	uint32_t header;
	uint32_t packetID;
	uint32_t sessionID;
	uint32_t packetLength;
	uint8_t* packetData;
	uint32_t packetCRC;
};


struct RawDataPack 
{
	uint8_t* data;
	size_t len;
};


// Send packet to target.
void SendPacket(const RabiDataPack& packet, SOCKET target);


#endif // _PACK_HEADER_

