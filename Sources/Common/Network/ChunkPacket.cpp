#include "ChunkPacket.h"

using namespace Network;

void ChunkPacket::Save(ByteStream& stream)
{
	for (int i = 0; i < BLOCK_SEND_COUNT; i++)
	{
		stream.Write(Blocks[i].Active);
		stream.Write(Blocks[i].Color.R);
		stream.Write(Blocks[i].Color.G);
		stream.Write(Blocks[i].Color.B);
	}
}
ChunkPacket ChunkPacket::Load(ByteStream& stream)
{
	ChunkPacket packet;
	for (int i = 0; i < BLOCK_SEND_COUNT; i++)
	{
		packet.Blocks[i].Active = stream.ReadBool();
		packet.Blocks[i].Color.R = stream.ReadByte();
		packet.Blocks[i].Color.G = stream.ReadByte();
		packet.Blocks[i].Color.B = stream.ReadByte(); 
	}
	return packet;
}
ChunkPacket::ChunkPacket()
{
}