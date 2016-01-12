#pragma once

namespace Watchtower
{
	class Rectangle // TODO: this is pretty primitive. consider expanding use, altho we dont need it
	{
	public:
		float Left;
		float Right;
		float Top;
		float Bottom;

		Rectangle();
		Rectangle(float left, float right, float top, float bottom);
	};
}