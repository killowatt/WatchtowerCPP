#pragma once
#include "../ByteStream.h"
#include "../Block.h"

namespace Watchtower
{
	struct ChunkPacket // We arent worried about optimization of network right now.
	{
		static const int BLOCK_SEND_COUNT = 256;
		Block Blocks[BLOCK_SEND_COUNT];

		void Save(ByteStream& stream);
		static ChunkPacket Load(ByteStream& stream);

		ChunkPacket();
	};
}