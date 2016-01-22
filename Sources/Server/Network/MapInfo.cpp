#include "MapInfo.h"
using namespace Watchtower;

MapInfo::MapInfo() : Name("Unnamed"), TotalChunks(0) {}
MapInfo::MapInfo(std::string name, int totalChunks)
{
	Name = name;
	TotalChunks = totalChunks;
}