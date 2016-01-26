#pragma once
#include <string>
#include <Chunk.h>
#include "Packet.h"

namespace Watchtower
{
	class MapInfo
	{
	public:
		std::string Name;
		unsigned int Width;
		unsigned int Height;

		static MapInfo Read(ByteStream& stream);
		ByteStream ToStream();

		MapInfo(std::string name, unsigned int width, unsigned int height);
	private:
		MapInfo();
	};
	class MapData
	{
	public:
		static void Read(ENetPacket* packet, Chunk* chunk);
		static ENetPacket* ToPacket(Chunk* chunk);
	};
}