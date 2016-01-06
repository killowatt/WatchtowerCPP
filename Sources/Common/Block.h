#pragma once
#include "Graphics/Color.h"

namespace Common
{
	struct Block
	{
		bool Active;
		Color Color;

		Block(bool active = false, Common::Color color = Common::Color());
	};
}
