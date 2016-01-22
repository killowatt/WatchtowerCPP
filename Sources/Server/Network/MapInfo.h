#pragma once
#include <string>

namespace Watchtower
{
	class MapInfo
	{
	public:
		std::string Name;
		unsigned int TotalChunks;

		MapInfo(std::string name, int totalChunks);
	private:
		MapInfo();
	};
}