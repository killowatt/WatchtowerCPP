#pragma once
#include "Packet.h"
#include "../Block.h"

namespace Network
{
	struct ChunkPacket : public Network::Packet<ChunkPacket>
	{
		uint32_t ChunkOffset;
		uint32_t BlockOffset;
		Block Block;

		void Save(MemoryStream& stream)
		{
			stream.Write(ChunkOffset);
			stream.Write(BlockOffset);
		}
		static ChunkPacket Load(MemoryStream& stream)
		{
			ChunkPacket packet;
			packet.ChunkOffset = stream.ReadInt();
			packet.BlockOffset = stream.ReadInt();
		}
	};
}