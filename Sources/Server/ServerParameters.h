#pragma once
#include <string>

namespace Watchtower
{
	class ServerParameters
	{
	public:
		std::string ServerIP;
		unsigned short Port;

		void Save();
		static ServerParameters Load();

		ServerParameters();
	private:
		void Parse(const std::string& key, const std::string& value);
	};
}