#include "GameMap.h"
#include <fstream>
#include <zlib/zlib.h>

using namespace Watchtower;

Chunk* const GameMap::GetData()
{
	return chunks;
}
Chunk& GameMap::GetChunk(unsigned int x, unsigned int y)
{
	if (x >= width || y >= height)
		throw 5445; // TODO: make proper error
	return chunks[width * y + x];
}

unsigned int GameMap::GetWidth() const { return width; }
unsigned int GameMap::GetHeight() const { return height; }

void GameMap::Save(const char* fileName)
{
	unsigned char* out = new unsigned char[sizeof(Chunk) * (width * height)];

	z_stream deflateStream;
	deflateStream.zalloc = Z_NULL;
	deflateStream.zfree = Z_NULL;
	deflateStream.opaque = Z_NULL;
	deflateStream.avail_in = sizeof(Chunk) * (width * height);
	deflateStream.next_in = (Bytef*)chunks;
	deflateStream.avail_out = sizeof(Chunk) * (width * height);
	deflateStream.next_out = (Bytef*)out;

	deflateInit(&deflateStream, Z_DEFAULT_COMPRESSION);
	deflate(&deflateStream, Z_FINISH);
	deflateEnd(&deflateStream);

	std::ofstream file(fileName, std::ios::binary);
	if (file.is_open())
	{
		file << width << height;
		file.write((char*)out, deflateStream.total_out);
	}
	file.close();
}
GameMap* GameMap::Load(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
	std::size_t size = file.tellg();

	GameMap* map = nullptr;
	unsigned char* in = nullptr;
	unsigned int width;
	unsigned int height;

	if (file.is_open())
	{
		file.seekg(0, std::ios::beg);
		file >> width >> height;

		map = new GameMap(width, height);
		in = new unsigned char[sizeof(Chunk) * (width * height)];

		file.read((char*)in, size - 8); // - 8 because we read two integers.
	}
	else { throw 500; } // TODO: errors!!!!!!!!!!!!!
	file.close();

	z_stream inflateStream;
	inflateStream.zalloc = Z_NULL;
	inflateStream.zfree = Z_NULL;
	inflateStream.opaque = Z_NULL;
	inflateStream.avail_in = sizeof(Chunk) * (width * height);
	inflateStream.next_in = (Bytef*)in;
	inflateStream.avail_out = sizeof(Chunk) * (width * height);
	inflateStream.next_out = (Bytef*)map->chunks;

	inflateInit(&inflateStream);
	inflate(&inflateStream, Z_NO_FLUSH);
	inflateEnd(&inflateStream);

	return map;
}

GameMap::GameMap(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	chunks = new Chunk[width * height];
}
GameMap::~GameMap()
{
	delete[] chunks;
}
