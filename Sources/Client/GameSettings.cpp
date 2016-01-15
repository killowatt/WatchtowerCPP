#include "GameSettings.h"
#include <fstream>
#include <sstream>
using namespace Watchtower;

const std::string GameSettings::FILENAME = "GameSettings.cfg";

void GameSettings::Save()
{
	std::ofstream stream(FILENAME);
	if (stream.is_open())
	{
		stream << "WindowWidth = " << WindowWidth << "\n";
		stream << "WindowHeight = " << WindowHeight << "\n";
		stream << "WindowType = " << static_cast<int>(WindowType) << "\n";
		stream << "VerticalSync = " << VerticalSync << "\n";
		stream.close();
	}
	else {}// TODO: throw error
}
GameSettings GameSettings::Load()
{
	GameSettings settings;
	std::ifstream stream(FILENAME);
	if (stream.is_open())
	{
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.at(0) == '#')
				continue;

			std::string key = line.substr(0, line.find(" "));
			std::string value = line.substr(line.find("=") + 1);

			if (!key.compare("WindowWidth")) settings.WindowWidth = std::stoul(value);
			else if (!key.compare("WindowHeight")) settings.WindowHeight = std::stoul(value);
			else if (!key.compare("WindowType")) 
				settings.WindowType = static_cast<Watchtower::WindowType>(std::stoul(value)); // TODO: avoid cast?
			else if (!key.compare("VerticalSync")) settings.VerticalSync = std::stoul(value);
			else {} // TODO: error
		}
	}
	else {} // TODO: error!!
	return settings;
}
GameSettings::GameSettings() 
{
	WindowWidth = 1280;
	WindowHeight = 720;
}