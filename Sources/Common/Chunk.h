#pragma once
#include "Block.h"

namespace Watchtower
{
	class Chunk
	{
	public:
		static const int CHUNK_WIDTH = 16;
		static const int CHUNK_HEIGHT = 128;
		static const int CHUNK_DEPTH = 16;

	private:
		Block blocks[CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH];

	public:
		Block& GetBlock(int x, int y, int z);
		void SetBlock(int x, int y, int z, Block block);

		Chunk();
		~Chunk();
	};
}
