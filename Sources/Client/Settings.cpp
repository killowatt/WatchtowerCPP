#include "Settings.h"
#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

using namespace Watchtower;

const std::string Settings::FILENAME = "Settings.cfg";

void Settings::Save()
{
	std::ofstream stream(FILENAME);
	if (stream.is_open())
	{
		stream << "WindowWidth = " << WindowWidth << "\n";
		stream << "WindowHeight = " << WindowHeight << "\n";
		stream.close();
	}
	else {}// TODO: throw error
}
Settings Settings::Load()
{
	Settings settings;
	std::ifstream stream(FILENAME);
	if (stream.is_open())
	{
		std::string line;
		std::string key;
		std::string value;
		std::stringstream string;
		while (std::getline(stream, line))
		{
			key = line.substr(0, line.find(" "));
			value = line.substr(line.find("=") + 1);

			if (!key.compare("WindowWidth")) settings.WindowWidth = std::stoul(value);
			else if (!key.compare("WindowHeight")) settings.WindowHeight = std::stoull(value);
			else std::cout << "key " << key << " not found.";

			//value = line.substr(key.length() + 3);

			//string.str(value);
			//string.clear();
			//if (!key.compare("WindowWidth ")) string >> settings.WindowWidth;
			//else if (!key.compare("WindowHeight ")) string >> settings.WindowHeight;
			//else
			//	std::cout << "key " << key << " not found.";
		}
	}
	else {} // TODO: error!!
	return settings;
}
Settings::Settings() 
{
	WindowWidth = 1280;
	WindowHeight = 720;
}