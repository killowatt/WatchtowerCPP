using System;
using System.IO;
using Watchtower;

namespace WatchtowerClient
{
    public enum WindowMode
    {
        Fullscreen = 1,
        BorderlessWindow = 2,
        Window = 3
    }
    public struct Settings
    {
        public int ResolutionWidth;
        public int ResolutionHeight;
        public WindowMode WindowMode;
        public int Display;

        public void Save(string path)
        {
            StreamWriter stream = new StreamWriter(path);

            stream.WriteLine("[ResolutionWidth] " + ResolutionWidth);
            stream.WriteLine("[ResolutionHeight] " + ResolutionHeight);
            stream.WriteLine("[WindowMode] " + (int)WindowMode);
            stream.WriteLine("[Display] " + Display);

            stream.Close();
        }
        public static Settings Load(string path) // TODO: good error handling everywhere.
        {
            Settings settings = new Settings { ResolutionWidth = 1280, ResolutionHeight = 720, WindowMode = WindowMode.Window, Display = -1 };
            //Settings settings = new Settings { ResolutionWidth = 960, ResolutionHeight = 540, WindowMode = WindowMode.Window, Display = -1 }; // Default Settings
            string[] lines;
            try
            {
                lines = File.ReadAllLines(path);
            }
            catch
            {
                Log.Print(MessageType.Warning, "Settings file failed to load due to an unknown error.");
                Log.Print(MessageType.Information, "Using default settings.");
                return settings;
            }

            foreach (string line in lines)
            {
                if (line.StartsWith("[ResolutionWidth] "))
                {
                    settings.ResolutionWidth = int.Parse(line.Replace("[ResolutionWidth] ", ""));  // TODO: error handle
                }
                if (line.StartsWith("[ResolutionHeight] "))
                {
                    settings.ResolutionHeight = int.Parse(line.Replace("[ResolutionHeight] ", ""));
                }
                if (line.StartsWith("[WindowMode] "))
                {
                    settings.WindowMode = (WindowMode)Enum.Parse(typeof(WindowMode), line.Replace("[WindowMode] ", ""));
                }
                if (line.StartsWith("[Display] "))
                {
                    settings.Display = int.Parse(line.Replace("[Display] ", ""));
                }
            }

            return settings;
        }
    }
}
