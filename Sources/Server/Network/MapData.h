#pragma once
#include <string>
#include "Packet.h"

namespace Watchtower
{
	class MapInfo
	{
	public:
		std::string Name;
		unsigned int TotalChunks;

		static MapInfo Read(ByteStream& stream);
		ByteStream ToStream();

		MapInfo(std::string name, int totalChunks);
	private:
		MapInfo();
	};
	class MapData
	{
	public:


		static MapData Read(ByteStream& stream);
		ByteStream ToStream();

		MapData();
	private:
		//MapData();
	};
}