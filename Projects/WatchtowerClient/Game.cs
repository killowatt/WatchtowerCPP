using System;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
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

        #region RAYCAST 2.0
        #endregion
        #region RAYCAST TEST
        public static bool callback(int xCopy, int yCopy, int zCopy, Vector3 face, Vector3 direction, bool active)
        {
            if ((xCopy > 0 && xCopy < 16) && (yCopy > 0 && yCopy < 128) && (zCopy > 0 && zCopy < 16))
            {
                if (chunk.Blocks[xCopy, yCopy, zCopy].Active)
                {



                    direction.Normalize();

                    face = new Vector3(0, 1, 0);

                    int theX = xCopy + (int)Math.Round(Math.Max((Math.Max(direction.X, direction.Y)), direction.Z));
                    int theY = yCopy + (int)Math.Round(Math.Max((Math.Max(direction.X, direction.Y)), direction.Z));
                    int theZ = zCopy + (int)Math.Round(Math.Max((Math.Max(direction.X, direction.Y)), direction.Z));
                    theX = xCopy + (int)face.X;
                    theY = yCopy + (int)face.Y;
                    theZ = zCopy + (int)face.Z;

                    if ((theX > 0 && theX < 16) && (theY > 0 && theY < 128) && (theZ > 0 && theZ < 16))
                    {
                        if (!active)
                        {
                            chunk.Blocks[xCopy, yCopy, zCopy].Active = false;
                        }
                        if (active)
                        {
                            chunk.Blocks[xCopy + (int)face.X, yCopy + (int)face.Y, zCopy + (int)face.Z].Active = true;
                            chunk.Blocks[xCopy + (int)face.X, yCopy + (int)face.Y, zCopy + (int)face.Z].Color =
                                Vector3.One;
                        }
                        return true;
                    }
                }
            }
            return false;
        }
        private static float mod(float value, float modulus) // So temporary
        {
            return (value % modulus + modulus) % modulus;
        }
        private static float intbound(float s, float ds)
        {
            if (ds < 0)
                return intbound(-s, -ds);

            s = mod(s, 1);
            return (1 - s) / ds;

        }
        private static int signum(float x)
        {
            return x > 0 ? 1 : x < 0 ? -1 : 0;
        }
        public static void DrawACube(Vector3 pos)
        {
            GL.Begin(BeginMode.Quads);

            GL.PopMatrix();
            GL.MatrixMode(MatrixMode.Modelview);
            GL.PushMatrix();
            GL.Translate(pos);
            GL.Vertex3(0.0, 0.0, 0.0);
            GL.Vertex3(0.5, 0.0, 0.0);
            GL.Vertex3(0.5, 0.5, 0.0);
            GL.Vertex3(0.0, 0.5, 0.0);

            GL.Vertex3(0.0, 0.0, -0.5);
            GL.Vertex3(0.5, 0.0, -0.5);
            GL.Vertex3(0.5, 0.5, -0.5);
            GL.Vertex3(0.0, 0.5, -0.5);

            GL.Vertex3(0.5, 0.0, 0.0);
            GL.Vertex3(0.5, 0.0, -0.5);
            GL.Vertex3(0.5, 0.5, -0.5);
            GL.Vertex3(0.5, 0.5, 0.0);

            GL.Vertex3(0.0, 0.0, 0.0);
            GL.Vertex3(0.0, 0.0, -0.5);
            GL.Vertex3(0.0, 0.5, -0.5);
            GL.Vertex3(0.0, 0.5, 0.0);

            GL.Vertex3(0.0, 0.5, 0.0);
            GL.Vertex3(0.5, 0.5, 0.0);
            GL.Vertex3(0.5, 0.5, -0.5);
            GL.Vertex3(0.0, 0.5, -0.5);

            GL.Vertex3(0.0, 0.0, 0.0);
            GL.Vertex3(0.5, 0.0, 0.0);
            GL.Vertex3(0.5, 0.0, -0.5);
            GL.Vertex3(0.0, 0.0, -0.5);

            GL.End();
        }
        private static void Raycast(Vector3 direction, float radius, bool active)
        {
            Vector3 origin = new Vector3(0, 0, 0);

            int x = (int)Math.Floor(Camera.X);
            int y = (int)Math.Floor(Camera.Y);
            int z = (int)Math.Floor(Camera.Z);

            int wx = 256;
            int wy = 256;
            int wz = 256; // WORLD BOUNDS

            float dx = direction.X;
            float dy = direction.Y;
            float dz = direction.Z;

            int stepX = signum(dx);
            int stepY = signum(dy);
            int stepZ = signum(dz);

            float tMaxX = intbound(Camera.X, dx);
            float tMaxY = intbound(Camera.Y, dy);
            float tMaxZ = intbound(Camera.Z, dz);

            float tDeltaX = stepX / dx;
            float tDeltaY = stepY / dy;
            float tDeltaZ = stepZ / dz;

            Vector3 face = new Vector3();

            // Avoids an infinite loop.
            if (dx == 0 && dy == 0 && dz == 0)
                return;

            // Rescale from units of 1 cube-edge to units of 'direction' so we can
            // compare with 't'.
            radius /= (float)Math.Sqrt(dx * dx + dy * dy + dz * dz);

            while (/* ray has not gone past bounds of world */
                   (stepX > 0 ? x < wx : x >= 0) &&
                   (stepY > 0 ? y < wy : y >= 0) &&
                   (stepZ > 0 ? z < wz : z >= 0))
            {

                // Invoke the callback, unless we are not *yet* within the bounds of the
                // world.
                if (!(x < 0 || y < 0 || z < 0 || x >= wx || y >= wy || z >= wz))
                    if (callback(x, y, z, face, direction, active))
                        break;

                if (tMaxX < tMaxY)
                {
                    if (tMaxX < tMaxZ)
                    {
                        if (tMaxX > radius) break;
                        // Update which cube we are now in.
                        x += stepX;
                        // Adjust tMaxX to the next X-oriented boundary crossing.
                        tMaxX += tDeltaX;
                        // Record the normal vector of the cube face we entered.
                        face.X = -stepX;
                        face.Y = 0;
                        face.Z = 0;
                    }
                    else
                    {
                        if (tMaxZ > radius) break;
                        z += stepZ;
                        tMaxZ += tDeltaZ;
                        face.X = 0;
                        face.Y = 0;
                        face.Z = -stepZ;
                    }
                }
                else
                {
                    if (tMaxY < tMaxZ)
                    {
                        if (tMaxY > radius) break;
                        y += stepY;
                        tMaxY += tDeltaY;
                        face.X = 0;
                        face.Y = -stepY;
                        face.Z = 0;
                    }
                    else
                    {
                        // Identical to the second case, repeated for simplicity in
                        // the conditionals.
                        if (tMaxZ > radius) break;
                        z += stepZ;
                        tMaxZ += tDeltaZ;
                        face.X = 0;
                        face.Y = 0;
                        face.Z = -stepZ;
                    }
                }
            }
        }

        #endregion

        private static Vector3 tempfirst;
        private static Vector3 tempsecond;
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
                //Window.CursorVisible = false;
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

            Vector3 diradd = direction * 8;
            if (Mouse.GetState().IsButtonDown(MouseButton.Left))
            {
                Raycast(direction, 8, false);
                chunk.Update(TestShader);
            }
            //if (Mouse.GetState().IsButtonDown(MouseButton.Right))
            //{
            //    Vector3 dirfixed = Vector3.Unproject(direction, 1280f / 2, 720f / 2, 0, 0, 0.5f, 1024f, Camera.View.Inverted());
            //    Raycast(dirfixed, 8, true);
            //    chunk.Update(TestShader);
            //}
            if (Keyboard.GetState().IsKeyDown(Key.E))
            {
                tempfirst = Camera.Position;
                tempsecond = Camera.Position + direction * 8;
            }
            //Draw3DLine((int)Camera.X, (int)Camera.Y, (int)Camera.Z, (int)diradd.X, (int)diradd.Y, (int)diradd.Z);
        }
        static void Render()
        {
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            chunk.Mesh.Draw();
            // TestMesh.Draw();
            GL.Begin(PrimitiveType.Lines);
            GL.Vertex3(tempfirst);
            GL.Vertex3(tempsecond);
            GL.Color3(255, 0, 0);
            GL.Color3(255, 0, 0);
            GL.End();

            DrawACube(new Vector3(80, 80, 80));

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
                        chunk.Blocks[x, y, z].Color = new Vector3((x / 15f), 40 / 255f, 94 / 255f);
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
