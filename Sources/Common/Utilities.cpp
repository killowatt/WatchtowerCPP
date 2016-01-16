#include "Utilities.h"
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <algorithm>
using namespace Watchtower;

std::string Utilities::FileReadAllLines(const char* fileName)
{
	std::ifstream fileStream(fileName);
	std::string file;

	if (fileStream.is_open())
	{
		fileStream.seekg(0, std::ios::end);
		file.reserve(fileStream.tellg());
		fileStream.seekg(0, std::ios::beg);

		file.assign((std::istreambuf_iterator<char>(fileStream)),
			std::istreambuf_iterator<char>());
	}
	return file;
}
void Utilities::StringRemoveWhitespace(std::string& string)
{
	string.erase(std::remove(string.begin(), string.end(), ' '), string.end());
}

