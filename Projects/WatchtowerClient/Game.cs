using System;
using System.Diagnostics;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace WatchtowerClient
{
    public static class Game
    {
        public static GraphicsContext GraphicsContext;
        public static NativeWindow Window;

        public static Stopwatch Time;
        public static bool Running;

        public static double x = 0;

        static void Update()
        {
        }
        static void Render()
        {
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            GraphicsContext.SwapBuffers();
        }
        public static void Initialize(Settings settings)
        {
            Running = false;
            Time = new Stopwatch();
            Window = new NativeWindow(settings.ResolutionWidth, settings.ResolutionHeight, "Watchtower",
                GameWindowFlags.Default, GraphicsMode.Default, DisplayDevice.GetDisplay((DisplayIndex)settings.Display));
            switch (settings.WindowMode)
            {
                case WindowMode.Window:
                    Window.WindowBorder = WindowBorder.Fixed;
                    Window.WindowState = WindowState.Normal;
                    break;
                case WindowMode.BorderlessWindow:
                    Window.WindowBorder = WindowBorder.Hidden;
                    Window.WindowState = WindowState.Normal;
                    break;
                case WindowMode.Fullscreen:
                    Window.WindowBorder = WindowBorder.Hidden;
                    Window.WindowState = WindowState.Fullscreen;
                    break;
                default:
                    Window.WindowBorder = WindowBorder.Fixed; // TODO: log
                    Window.WindowState = WindowState.Normal;
                    break;
            }

            GraphicsContext = new GraphicsContext(GraphicsMode.Default, Window.WindowInfo);
            GraphicsContext.LoadAll();
            GraphicsContext.SwapInterval = 0;
            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.Blend);
            GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);
            GL.ClearColor(15 / 255f, 15 / 255f, 15 / 255f, 1);

            Window.Visible = true;
            Running = true;
            Time.Start();

            int tickRate = 16;
            double millisecondsPerUpdate = 1000.0 / tickRate;
            double previous = Time.Elapsed.TotalMilliseconds;
            double lag = 0;
            while (Running)
            {
                double current = Time.Elapsed.TotalMilliseconds;
                double elapsed = current - previous;
                previous = current;
                lag += elapsed;

                // processinput

                while (lag >= millisecondsPerUpdate) // temp
                {
                    Update();
                    lag -= millisecondsPerUpdate;
                }

                Render();
            }
        }
    }
}
