#pragma once
#include <string>

namespace Watchtower
{
	class Log
	{
	public:
		enum class Channel
		{
			General,
			System,
			Renderer
		};
		void Print(Channel channel, const char* message);
		void Print(Channel channel, const std::string& message);
		void Print(const char* message);
		void Print(const std::string& message);
	};
}