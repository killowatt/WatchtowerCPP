#include "Color.h"
using namespace Watchtower;

Color::Color() : Color(0, 0, 0) {}
Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	R = r;
	G = g;
	B = b;
}