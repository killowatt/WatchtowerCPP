#include "GameSettings.h"
#include <fstream>
#include <sstream>
#include <Utilities.h>
using namespace Watchtower;

const std::string GameSettings::FILENAME = "GameSettings.ini";

void GameSettings::Save()
{
	std::ofstream file(FILENAME);
	if (file.is_open())
	{
		file << "PlayerName = " << PlayerName << "\n";
		file << "WindowWidth = " << WindowWidth << "\n";
		file << "WindowHeight = " << WindowHeight << "\n";
		file << "WindowType = " << static_cast<int>(WindowType) << "\n";
		file << "VerticalSync = " << VerticalSync << "\n";
		file.close();
	}
	else {}// TODO: throw error
}
GameSettings GameSettings::Load()
{
	GameSettings settings;
	std::istringstream file(Utilities::FileReadAllLines(FILENAME.c_str()));
	std::string line;
	while (std::getline(file >> std::ws, line))
	{
		std::istringstream lineStream(line);
		std::string key;
		if (std::getline(lineStream >> std::ws, key, '='))
		{
			Utilities::StringRemoveWhitespace(key); // TODO: is there a better way to remove trailing
			std::string value;
			if (std::getline(lineStream >> std::ws, value))
				settings.Parse(key, value);
		}
	}
	settings.Save();
	return settings;
}
void GameSettings::Parse(const std::string& key, const std::string& value)
{
	if (key == "PlayerName") PlayerName = value;
	if (key == "WindowWidth") WindowWidth = std::stoul(value);
	if (key == "WindowHeight") WindowHeight = std::stoul(value);
	if (key == "WindowType") WindowType = std::stoul(value);
	if (key == "VerticalSync") VerticalSync = std::stoul(value);
}

GameSettings::GameSettings() 
{
	PlayerName = "Player";
	WindowWidth = 1280;
	WindowHeight = 720;
	WindowType = Watchtower::WindowType::Window;
	VerticalSync = true;
}