#pragma once
#include <string>
#include "Packet.h"
namespace Watchtower
{
	class ClientData
	{
	public:
		unsigned char PacketType;
		std::string PlayerName;
	};
}