#pragma once
#include <string>

namespace Watchtower
{
	enum class WindowType
	{
		Fullscreen = 0,
		BorderlessWindow = 1,
		Window = 2
	};
	class Settings
	{
	public:
		static const std::string FILENAME;
		unsigned int WindowWidth;
		unsigned int WindowHeight;
		WindowType WindowType;
		bool VerticalSync;

		void Save();
		static Settings Load();

		Settings();
	};
}