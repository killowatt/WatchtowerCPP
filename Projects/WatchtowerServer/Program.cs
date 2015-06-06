using System;
using System.Linq;
using System.Net;
using Lidgren.Network;

namespace WatchtowerServer
{
    static class Program
    {
        static void Main()
        {
            // test infrastructure
            NetPeerConfiguration config = new NetPeerConfiguration("Watchtower");
            config.Port = 26555;

            NetServer server = new NetServer(config);
            server.Start();

            Console.Title = "SERVER";
            Console.ForegroundColor = ConsoleColor.White;

            NetIncomingMessage message;
            while (true)
            {
                while ((message = server.ReadMessage()) != null)
                {
                    switch (message.MessageType)
                    {
                        case NetIncomingMessageType.StatusChanged:
                            NetConnectionStatus status = (NetConnectionStatus)message.ReadByte();

                            string reason = message.ReadString();
                            Console.WriteLine(NetUtility.ToHexString(message.SenderConnection.RemoteUniqueIdentifier) +
                                              " " + status + ": " + reason);

                            if (status == NetConnectionStatus.Connected)
                            {
                                Console.WriteLine("Hail: " + message.SenderConnection.RemoteHailMessage.ReadString());

                                NetOutgoingMessage sendmessage = server.CreateMessage();
                                sendmessage.Write("hey");


                                Console.WriteLine("Ready to reply. Press any key to send message.");
                                Console.ReadKey();

                                server.SendMessage(sendmessage, server.Connections.First(),
                                    NetDeliveryMethod.ReliableOrdered);
                            }
                            break;
                    }
                }
            }

            //Console.ForegroundColor = ConsoleColor.White;
            //Console.WriteLine("Ready. Press any key to send message.");
            //Console.ReadKey();

            //NetOutgoingMessage sendMessage = server.CreateMessage();
            //sendMessage.Write("HELLO");
            //sendMessage.Write("WORLD");
            //server.SendMessage(sendMessage, null, NetDeliveryMethod.ReliableOrdered);

            //Console.WriteLine("Message sent. Waiting for reply. NOT YET IMPLEMENTED");
        }
    }
}
