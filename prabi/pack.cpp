#include "pack.h"

void SendPacket(const RabiDataPack& packet, SOCKET target)
{
	SendData(target, "RABI", 4);
	SendData(target, &packet.packetType, sizeof(packet.packetType));
	SendData(target, &packet.sessionID, sizeof(packet.sessionID));
	SendData(target, &packet.packetLength, sizeof(packet.packetLength));
	SendData(target, &packet.packetData, packet.packetLength);
}

RabiDataPack RecivePacket(SOCKET remote)
{
	RabiDataPack res;
	char header[4];
	ReciveData(remote, header, 4);
	if (memcmp(header, "RABI", 4) != 0)
		throw std::exception("bad header!");
	ReciveData(remote, &res.packetType, sizeof(res.packetType));
	ReciveData(remote, &res.sessionID, sizeof(res.sessionID));
	ReciveData(remote, &res.packetLength, sizeof(res.packetLength));
	auto buffer = new uint8_t[res.packetLength];
	ReciveData(remote, buffer, res.packetLength);
	res.packetData = std::shared_ptr<uint8_t>(buffer, std::default_delete<uint8_t[]>());
	return res;
}

RabiDataPack::~RabiDataPack()
{

}
