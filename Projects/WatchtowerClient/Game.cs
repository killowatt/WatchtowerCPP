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
        public static Mesh[,,] MeshArray;

        static void Update()
        {
            Window.ProcessEvents();
            
        }
        static void Render()
        {
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            TestMesh.Draw();
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 16; y++)
                {
                    for (int z = 0; z < 16; z++)
                    {
                        MeshArray[x, y, z].Draw();
                    }
                }
            }

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
            TestMesh = new Mesh(new VertexData()
            {
                Vertices = new float[]
                {
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f
                },
                Indices = new uint[]
                {
                    0, 1, 2,
                    2, 3, 0,
                    4, 5, 7,
                    7, 6, 5,
                    3, 4, 5,
                    3, 2, 5,
                    6, 5, 2,
                    1, 6, 2,
                    7, 6, 1,
                    0, 7, 1,
                    7, 4, 3,
                    0, 7, 3
                }
            }, TestShader);
            MeshArray = new Mesh[32, 32, 32];
            for (int x = 0; x < 32; x++)
            {
                for (int y = 0; y < 32; y++)
                {
                    for (int z = 0; z < 32; z++)
                    {
                        MeshArray[x, y, z] = TestMesh.Copy();
                        MeshArray[x, y, z].Transform = Matrix4.CreateTranslation(x, y, z);
                    }
                }
            }

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
