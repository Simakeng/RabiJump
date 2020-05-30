#pragma once
#ifndef _PACK_HEADER_
#define _PACK_HEADER_
#include "os.h"
struct DataPack
{
	uint32_t header;
	uint32_t packetID;
	uint16_t sessionID;
	union
	{
		uint32_t l32;
		uint16_t l16;
		uint8_t l8;
	} packetLength;
	uint32_t packetCRC;
	uint8_t* packetData;
};

/// <summary>
/// Send packet to target.
/// </summary>
void SendPacket(const DataPack& packet, SOCKET target);

#endif // _PACK_HEADER_

