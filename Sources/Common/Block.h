#pragma once
#include "Graphics/Color.h"

namespace Watchtower
{
	struct Block
	{
		bool Active;
		Color Color;

		Block(bool active = false, Watchtower::Color color = Watchtower::Color());
	};
}
