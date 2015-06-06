using System;

namespace Watchtower
{
    public enum MessageType // TODO: expand logger to optionally print to files/ingame console/etc.
    {
        System = 1,
        Information = 2, // TODO: flags system? i.e. system, info / information, error
        Warning = 3,
        Error = 4
    }
    public static class Log
    {
        public static void Print(MessageType messageType, string text)
        {
            Console.BackgroundColor = ConsoleColor.Black;
            switch (messageType)
            {
                case MessageType.System:
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.Write("[SYSTEM]");
                    break;
                case MessageType.Information:
                    Console.ForegroundColor = ConsoleColor.Blue;
                    Console.Write("[INFO]");
                    break;
                case MessageType.Warning:
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.Write("[WARNING]");
                    break;
                case MessageType.Error:
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write("[ERROR]");
                    break;
                default:
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.Write("[UNKNOWN]");
                    break;
            }
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(" " + text);
        }
    }
}
