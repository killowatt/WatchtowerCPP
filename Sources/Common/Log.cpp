#include "Log.h"
#include <iostream>
using namespace Watchtower;

inline std::string GetChannelName(Log::Channel channel)
{
	switch (channel)
	{
	case Log::Channel::General:
		return "[General] ";
		break;
	case Log::Channel::System:
		return "[System] ";
		break;
	case Log::Channel::Renderer:
		return "[Renderer] ";
		break;
	default:
		return "[Unknown] ";
		break;
	}
}
void Log::Print(Log::Channel channel, const char* message)
{
	std::cout << GetChannelName(channel) << message << "\n";
}
void Log::Print(Log::Channel channel, const std::string& message) { Print(channel, message); }
void Log::Print(const char* message) { Print(Log::Channel::General, message); }
void Log::Print(const std::string& message) { Print(Log::Channel::General, message); }