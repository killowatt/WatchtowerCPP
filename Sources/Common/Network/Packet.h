#pragma once
#include "../MemoryStream.h"

namespace Network
{
	template<typename T>
	class Packet
	{
		virtual void Save(MemoryStream& stream) = 0;
		virtual static T Load(MemoryStream& stream) = 0;
	};
}