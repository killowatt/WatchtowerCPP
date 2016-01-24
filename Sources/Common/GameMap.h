#pragma once
#include "Chunk.h"
#include <string>

namespace Watchtower
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

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		uint64_t GetTotalChunks() const; // TODO: maybe we should always use cstdint

		void Save(const char* fileName);
		static GameMap* Load(const char* fileName);

		GameMap() = delete;
		GameMap(unsigned int width, unsigned int height);
		~GameMap();
	};
}
