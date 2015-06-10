﻿using System;
using System.IO;
using Lidgren.Network;
using OpenTK;
using WatchtowerClient.Graphics;

namespace WatchtowerClient
{
    static class Program
    {
        static void Main()
        {
            #region NetTest
            //NetPeerConfiguration config = new NetPeerConfiguration("Watchtower");
            //config.Port = 26556;

            //Console.Title = "CLIENT";
            //Console.ForegroundColor = ConsoleColor.White;
            //Console.WriteLine("Press any key to connect.");
            //Console.ReadKey();

            //NetClient client = new NetClient(config);
            //client.Start();
            //NetOutgoingMessage hailMessage = client.CreateMessage("Hello");
            //client.Connect("localhost", 26555, hailMessage);
            ////Settings settings = Settings.Load("Settings.txt");
            ////Game.Initialize(settings);
            //NetIncomingMessage incomingMessage;
            //while (true)
            //{
            //    while ((incomingMessage = client.ReadMessage()) != null)
            //    {
            //        Console.WriteLine("Server:" + incomingMessage.ReadString());
            //    }
            //}
            //
            //Console.ReadKey();
            #endregion


             float[] x = new float[]
                {
                    0.5f, 0.5f, -0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, 0.5f
                };
            VertexData xyzd = new VertexData();
            xyzd.Vertices = x;
            xyzd.Add(xyzd);
            


            Settings settings = Settings.Load("Settings.txt");
            if (!File.Exists("Settings.txt"))
            {
                settings.Save("Settings.txt");
            }
            Game.Initialize(settings);
        }
    }
}
