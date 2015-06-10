using System;
using System.Diagnostics;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Assets.Shaders;
using WatchtowerClient.Graphics;

namespace WatchtowerClient
{
    public static class Game
    {
        public static GraphicsContext GraphicsContext;
        public static NativeWindow Window;

        public static Stopwatch Time;
        public static bool Running;

        public static BasicShader TestShader;
        public static Mesh TestMesh;
        public static Chunk chunk;

        static void Update()
        {
            Window.ProcessEvents();
        }
        static void Render()
        {
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            chunk.Mesh.Draw();
           // TestMesh.Draw();

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

            // TEMP
            TestShader = new BasicShader();
            chunk = new Chunk();
            chunk.Blocks[0, 2, 0].Active = false;
            for (int i = 0; i < 128; i++)
            {
                chunk.Blocks[15, i, 15].Active = false;
                chunk.Blocks[14, i, 15].Active = false;
                chunk.Blocks[13, i, 15].Active = false;
            }
            chunk.Update(TestShader);

          //  TestMesh = new Mesh(Block.BuildCube(true, true, false, true, false, true), TestShader);
          //  TestMesh.Transform = Matrix4.CreateTranslation(22, 22, 22);

            Console.WriteLine(TestShader.GetCompileStatus(ShaderType.VertexShader));
            Console.WriteLine(TestShader.GetCompileStatus(ShaderType.FragmentShader));
            Console.WriteLine(TestShader.GetCompileLog(ShaderType.VertexShader));
            Console.WriteLine(TestShader.GetCompileLog(ShaderType.FragmentShader));
            // TEMP


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
