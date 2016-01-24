#pragma once
#include <string>
#include "Packet.h"

namespace Watchtower
{
	class ClientData : public Packet
	{
	public:
		std::string PlayerName;

		static ClientData Read(ByteStream& stream);
		ByteStream ToStream();

		ClientData(std::string playerName);
	private:
		ClientData();
	};
}