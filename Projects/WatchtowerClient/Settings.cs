using System;
using System.IO;

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
        public int WindowWidth;
        public int WindowHeight;
        public WindowMode WindowMode;

        public void Save(string path)
        {
            StreamWriter stream = new StreamWriter(path);

            stream.WriteLine("[WindowWidth] " + WindowWidth);
            stream.WriteLine("[WindowHeight] " + WindowHeight);
            stream.WriteLine("[WindowMode] " + (int) WindowMode);

            stream.Close();
        }
        public Settings Load(string path)
        {
            Settings settings = new Settings { WindowWidth = 960, WindowHeight = 540, WindowMode = WindowMode.Window };
            string[] lines = File.ReadAllLines(path);

            foreach (string line in lines)
            {
                if (line.StartsWith("[WindowWidth] "))
                {
                    settings.WindowWidth = int.Parse(line.Replace("[WindowWidth] ", ""));
                }
                if (line.StartsWith("[WindowHeight] "))
                {
                    settings.WindowHeight = int.Parse(line.Replace("[WindowHeight] ", ""));
                }
                if (line.StartsWith("[WindowMode] "))
                {
                    settings.WindowMode = (WindowMode)Enum.Parse(typeof (WindowMode), line.Replace("[WindowMode] ", ""));
                }
            }

            return settings;
        }
    }
}
