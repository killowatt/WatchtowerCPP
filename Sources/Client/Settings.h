#pragma once
#include <string>

namespace Watchtower
{
	class Settings
	{
	public:
		static const std::string FILENAME;
		unsigned int WindowWidth;
		unsigned int WindowHeight;

		void Save();
		static Settings Load();

		Settings();
	};
}