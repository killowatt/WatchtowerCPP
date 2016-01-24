#include "ClientData.h"
using namespace Watchtower;

ClientData ClientData::Read(ByteStream& stream)
{
	ClientData clientData;
	clientData.PlayerName = stream.ReadString();
	return clientData;
}
ByteStream ClientData::ToStream()
{
	ByteStream stream;
	stream.Write((char)PacketType::ClientData);
	stream.Write(PlayerName);
	return stream;
}

ClientData::ClientData() : PlayerName("Player") {}
ClientData::ClientData(std::string playerName)
{
	PlayerName = playerName;
}