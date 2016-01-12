#pragma once
#include <cstdint>

namespace Watchtower
{
	struct Color
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;

		Color();
		Color(uint8_t r, uint8_t g, uint8_t b);
	};
}