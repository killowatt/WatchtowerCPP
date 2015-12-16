#include "Rectangle.h"

using namespace Graphics;

Rectangle::Rectangle() : Left(0), Right(0), Top(0), Bottom(0) {}
Rectangle::Rectangle(float left, float right, float top, float bottom)
{
	Left = left;
	Right = right;
	Top = top;
	Bottom = bottom;
}