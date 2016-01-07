#pragma once
#include "Chunk.h"

namespace Common
{
	class GameMap
	{
	protected:
		Chunk* chunks;

		unsigned int width;
		unsigned int height;

	public:
		Chunk* const GetData();
		Chunk& GetChunk(unsigned int x, unsigned int y); // TODO: consider the overall system for blocks and chunks and how it can be improved..

		unsigned int GetWidth();
		unsigned int GetHeight();

		GameMap() = delete;
		GameMap(unsigned int width, unsigned int height);
		~GameMap();
	};
}