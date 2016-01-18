#pragma once
#include <string>

namespace Watchtower
{
	class ServerParameters
	{
	public:
		const static std::string FILENAME;

		std::string ServerIP;
		unsigned short Port;
		unsigned short MaxPlayers;

		void Save();
		static ServerParameters Load();

		ServerParameters();

	private:
		void Parse(const std::string& key, const std::string& value);
	};
}