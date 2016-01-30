#pragma once

namespace Watchtower
{
	class Error
	{
		enum class ErrorType
		{
			General
		};
		void Throw(/*type, message, etc.*/); // TODO:
	};
}