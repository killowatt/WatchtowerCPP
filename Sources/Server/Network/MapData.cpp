#include "MapData.h"
#include <zlib/zlib.h>
using namespace Watchtower;

MapInfo MapInfo::Read(ByteStream& stream)
{
	MapInfo mapInfo;
	mapInfo.Name = stream.ReadString();
	mapInfo.Width = stream.ReadUnsignedInt();
	mapInfo.Height = stream.ReadUnsignedInt();
	return mapInfo;
}
ByteStream MapInfo::ToStream()
{
	ByteStream stream;
	stream.Write((char)PacketType::MapInfo);
	stream.Write(Name);
	stream.Write(Width);
	stream.Write(Height);
	return stream;
}

MapInfo::MapInfo() : Name("Untitled Map"), Width(0), Height(0) {}
MapInfo::MapInfo(std::string name, unsigned int width, unsigned int height)
{
	Name = name;
	Width = width;
	Height = height;
}

void MapData::Read(ENetPacket* packet, Chunk* chunk)
{
	z_stream inflateStream;
	inflateStream.zalloc = Z_NULL;
	inflateStream.zfree = Z_NULL;
	inflateStream.opaque = Z_NULL;
	inflateStream.avail_in = sizeof(Chunk);
	inflateStream.next_in = (Bytef*)packet->data + 1; // +1 for packet type
	inflateStream.avail_out = sizeof(Chunk);
	inflateStream.next_out = (Bytef*)chunk;

	inflateInit(&inflateStream);
	inflate(&inflateStream, Z_NO_FLUSH);
	inflateEnd(&inflateStream);
}
ENetPacket* MapData::ToPacket(Chunk* chunk)
{
	unsigned char* out = new unsigned char[sizeof(Chunk) + 1]; // TODO: reuse single allocation?
	out[0] = (char)PacketType::MapData;              // ^ +1 for packet type :)

	z_stream deflateStream;
	deflateStream.zalloc = Z_NULL;
	deflateStream.zfree = Z_NULL;
	deflateStream.opaque = Z_NULL;
	deflateStream.avail_in = sizeof(Chunk);
	deflateStream.next_in = (Bytef*)chunk;
	deflateStream.avail_out = sizeof(Chunk);
	deflateStream.next_out = (Bytef*)out + 1;

	deflateInit(&deflateStream, Z_DEFAULT_COMPRESSION);
	deflate(&deflateStream, Z_FINISH);
	deflateEnd(&deflateStream);

	ENetPacket* packet = enet_packet_create(out, deflateStream.total_out, ENET_PACKET_FLAG_RELIABLE);
	delete[] out;
	return packet;
}


