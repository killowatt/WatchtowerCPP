#pragma once
#include <enet/enet.h>
#include <ByteStream.h>

namespace Watchtower
{
	namespace PacketType
	{
		enum PacketType
		{
			ClientData = 0,
			ClientDataReceived = 1,
			MapInfo = 2,
			MapData = 3
		};
	}
	class Packet
	{
		virtual ByteStream ToStream() = 0;
	};
}