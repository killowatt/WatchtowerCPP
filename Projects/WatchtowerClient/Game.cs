using System;
using System.Diagnostics;
using System.Dynamic;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Input;
using Watchtower;
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

        public static Camera Camera;

        public static BasicShader TestShader;
        public static Mesh TestMesh;
        public static Chunk chunk;

        private static Vector2 lastMouse;
        public static Matrix4 VIEWTEMP;

        static void Update(double deltaTime)
        {
            Window.ProcessEvents();

            // p. much everything here is temp test
            if (Keyboard.GetState().IsKeyDown(Key.Escape))
            {
                Running = false;
            }
            if (Keyboard.GetState().IsKeyDown(Key.F1))
            {
                Log.Print(MessageType.System, "Break");
            }

            MouseState mouseState = Mouse.GetCursorState();
            int x = mouseState.X;
            int y = mouseState.Y;
            if (Window.Focused)
            {
                Mouse.SetPosition(1920f / 2, 1080f / 2);
                Window.CursorVisible = false;
            }
            if (!Window.Focused)
            {
                Window.CursorVisible = true;
            }

            float mouseSpeed = 0.005f;


            Vector3 direction = new Vector3(
                (float)(Math.Cos(Camera.Pitch * (Math.PI / 180)) * Math.Sin(Camera.Yaw * (Math.PI / 180))),
                (float)(Math.Sin(Camera.Pitch * (Math.PI / 180))),
                (float)(Math.Cos(Camera.Pitch * (Math.PI / 180)) * Math.Cos(Camera.Yaw * (Math.PI / 180)))
                );

            direction.Normalize();

            Vector3 right = new Vector3(
                (float)(Math.Sin((Camera.Yaw * (Math.PI / 180)) - 3.14f / 2.0f)),
                0,
                (float)(Math.Cos((Camera.Yaw * (Math.PI / 180)) - 3.14f / 2.0f))
                );

            Vector3 up = Vector3.Cross(right, direction);

            right.Normalize();

           // if (mouseState.IsButtonDown(MouseButton.Left))
           // {
            if (Window.Focused)
            {
                Camera.Yaw += mouseSpeed * (float)16 * (1920f / 2f - x);
                Camera.Pitch += mouseSpeed * (float)16 * (1080f / 2f - y);
            }

            //}

            float speed = 0.025f;

            KeyboardState state = Keyboard.GetState();
            if (Keyboard.GetState().IsKeyDown(Key.W))
            {
                Camera.Position += direction * (float)deltaTime * speed;
            }
            if (Keyboard.GetState().IsKeyDown(Key.S))
            {
                Camera.Position -= direction * (float)deltaTime * speed;
            }
            if (Keyboard.GetState().IsKeyDown(Key.D))
            {
                Camera.Position += right * (float)deltaTime * speed;
            }
            if (Keyboard.GetState().IsKeyDown(Key.A))
            {
                Camera.Position -= right * (float)deltaTime * speed;
            }
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

            Camera = new Camera();
            Camera.Position = new Vector3(0, 60, 60);
            Camera.Yaw = 180;

            // TEMP
            TestShader = new BasicShader();
            chunk = new Chunk();
            chunk.Blocks[0, 2, 0].Active = false;
            for (int x = 0; x < 16; x += 2)
            {
                for (int y = 0; y < 128; y += 2)
                {
                    for (int z = 0; z < 16; z++)
                    {
                        chunk.Blocks[x, y, z].Active = false;
                    }
                }
            }
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 128; y++)
                {
                    for (int z = 0; z < 16; z++)
                    {
                        chunk.Blocks[x, y, z].Color = new Vector3((y / 127f), 40 / 255f, 94 / 255f);
                    }
                }
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

            double previous = Time.Elapsed.TotalMilliseconds;
            while (Running)
            {
                double current = Time.Elapsed.TotalMilliseconds;
                double elapsed = current - previous;
                // processInput?
                Update(elapsed);
                Render();
                previous = current;
            }
            //int tickRate = 512;
            //double millisecondsPerUpdate = 1000.0 / tickRate;
            //double previous = Time.Elapsed.TotalMilliseconds;
            //double lag = 0;
            // Old loop
            //while (Running) 
            //{
            //    double current = Time.Elapsed.TotalMilliseconds;
            //    double elapsed = current - previous;
            //    previous = current;
            //    lag += elapsed;

            //    // processinput

            //    while (lag >= millisecondsPerUpdate) // temp
            //    {
            //        Update(lag / millisecondsPerUpdate);
            //        lag -= millisecondsPerUpdate;
            //    }

            //    Render();
            //}

        }
    }
}
