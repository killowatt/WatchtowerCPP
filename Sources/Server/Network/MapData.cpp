#include "MapData.h"
using namespace Watchtower;

MapInfo MapInfo::Read(ByteStream& stream)
{
	MapInfo mapInfo;
	mapInfo.Name = stream.ReadString();
	mapInfo.TotalChunks = stream.ReadUnsignedInt();
	return mapInfo;
}
ByteStream MapInfo::ToStream()
{
	ByteStream stream;
	stream.Write((char)PacketType::MapInfo);
	stream.Write(Name);
	stream.Write(TotalChunks);
	return stream;
}

MapInfo::MapInfo() : Name("Untitled Map"), TotalChunks(0) {}
MapInfo::MapInfo(std::string name, int totalChunks)
{
	Name = name;
	TotalChunks = totalChunks;
}