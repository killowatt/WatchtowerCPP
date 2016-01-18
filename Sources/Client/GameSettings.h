#pragma once
#include <string>

namespace Watchtower
{
	namespace WindowType
	{
		enum WindowType
		{
			Fullscreen = 0,
			BorderlessWindow = 1,
			Window = 2
		};
	}
	class GameSettings
	{
	public:
		static const std::string FILENAME;
		std::string PlayerName; // TODO: this!!
		unsigned int WindowWidth;
		unsigned int WindowHeight;
		unsigned char WindowType;
		bool VerticalSync;

		void Save();
		static GameSettings Load();

		GameSettings();
	private:
		void Parse(const std::string& key, const std::string& value);
	};
}