#include "ServerParameters.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Utilities.h>
using namespace Watchtower;

void ServerParameters::Save()
{
	std::ofstream file;
	if (file.is_open())
	{
		file << "ServerIP = " << ServerIP;
		file << "Port = " << Port;
		file.close();
	}
	else {} // TODO: error
}
ServerParameters ServerParameters::Load()
{
	ServerParameters settings;
	std::istringstream file(Utilities::FileReadAllLines("Server.ini"));
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
	return settings;
}
void ServerParameters::Parse(const std::string& key, const std::string& value)
{
	if (key == "ServerIP")
		ServerIP = value;
	else if (key == "Port")
		Port = std::stoul(value);
	else {} // TODO: no matching key!
}

ServerParameters::ServerParameters()
{
	ServerIP = "";
	Port = 22737;
	MaxPlayers = 128;
}