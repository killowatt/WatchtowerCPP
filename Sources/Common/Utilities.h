#pragma once
#include <string>

namespace Watchtower
{
	class Utilities
	{
	public:
		static std::string FileReadAllLines(const char* fileName);
		static void StringRemoveWhitespace(std::string& string);
	};
}