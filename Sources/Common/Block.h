#pragma once
#include "Graphics/Color.h"

struct Block
{
	bool Active;
	Graphics::Color Color;

	Block(bool active = false, Graphics::Color color = Graphics::Color());
};
