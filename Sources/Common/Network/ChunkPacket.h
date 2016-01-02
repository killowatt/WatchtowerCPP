#pragma once
#include "../MemoryStream.h"
#include "../Block.h"

namespace Network
{
	struct ChunkPacket // We arent worried about optimization of network right now.
	{
		static const int BLOCK_SEND_COUNT = 256;
		Block Blocks[BLOCK_SEND_COUNT];

		void Save(MemoryStream& stream);
		static ChunkPacket Load(MemoryStream& stream);

		ChunkPacket();
	};
}