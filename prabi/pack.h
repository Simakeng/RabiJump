#pragma once
#ifndef _PACK_HEADER_
#define _PACK_HEADER_
#include "os.h"

struct RawDataPack
{
	uint32_t header;
	uint32_t packetID;
	uint32_t sessionID;
	uint32_t packetLength;
	uint8_t* packetData;
	uint32_t packetCRC;
};


// Send packet to target.
void SendPacket(const RawDataPack& packet, SOCKET target);


#endif // _PACK_HEADER_

