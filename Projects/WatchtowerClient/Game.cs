using System;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.Drawing.Imaging;
using System.Dynamic;
using System.Runtime.InteropServices;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Input;
using Watchtower;
using WatchtowerClient.Assets.Shaders;
using WatchtowerClient.Graphics;
using PixelFormat = System.Drawing.Imaging.PixelFormat;

namespace WatchtowerClient
{
    public static class Game
    {
        public static GraphicsContext GraphicsContext;
        public static NativeWindow Window;

        public static Stopwatch Time;
        public static bool Running;

        public static Mesh FramebufferMesh;

        public static Camera Camera;

        public static BasicShader TestShader;
        public static Mesh TestMesh;
        public static Chunk chunk;

        public static Chunk[,] WORLDCHUNKS;

        //private static Vector2 lastMouse;
        public static Matrix4 VIEWTEMP;
        public static Vector3 direction;

        public static Framebuffer NormalBuffer;
        public static Framebuffer ColorBuffer;
        public static Framebuffer DepthBuffer;
        public static Framebuffer FinalBuffer;
        public static FramebufferShader fbshader;
        //private static Vector3 tempasset;

        #region MAP LOADER 2015
        private static void GenerateChunksFromThatMapYouKnow() // TODO: the loading of this needs to be not bad
        {
            Bitmap bitmap = new Bitmap("Textures/terrain.png");
            BitmapData bitmapData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);

            IntPtr ptr = bitmapData.Scan0;

            int bytes = bitmapData.Stride * bitmap.Height;
            byte[] rgbValues = new byte[bytes];
            byte[] r = new byte[bytes / 3];
            byte[] g = new byte[bytes / 3];
            byte[] b = new byte[bytes / 3];

            Marshal.Copy(ptr, rgbValues, 0, bytes);

            int count = 0;
            int stride = bitmapData.Stride;

            for (int row = 0; row < bitmapData.Height; row++)
            {
                for (int column = 0; column < bitmapData.Width; column++)
                {
                    b[count] = (byte)(rgbValues[(row * stride) + (column * 3)]);
                    g[count] = (byte)(rgbValues[(row * stride) + (column * 3) + 1]);
                    r[count++] = (byte)(rgbValues[(row * stride) + (column * 3) + 2]);
                }
            }

            WORLDCHUNKS = new Chunk[16,16];
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 16; y++)
                {
                    WORLDCHUNKS[x, y] = new Chunk();
                }
            }

            for (int cx = 0; cx < 16; cx++)
            {
                for (int cy = 0; cy < 16; cy++)
                {
                    for (int bx = 0; bx < 16; bx++)
                    {
                        for (int by = 0; by < 16; by++)
                        {                                                                                // V THIS IS TO SCALE IT DOWN
                            for (int bz = 0; bz < r[(bitmap.Width * (bx + (cx * 16))) + (by + (cy * 16))] / 1; bz++)
                            {
                                WORLDCHUNKS[cx, cy].Blocks[bx, bz, by].Active = true;
                                WORLDCHUNKS[cx, cy].Blocks[bx, bz, by].Color =
                                    //new Vector3((234 / 255f), (181 / 255f), (65 / 255f));
                                    new Vector3((bz / 127f), 40 / 255f, 94 / 255f);
                            }
                        }
                    }
                }
            }
            // these arent put together since i need some mental clarity y'know yea
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 16; y++)
                {
                    WORLDCHUNKS[x, y].Mesh.Transform = Matrix4.CreateTranslation(x * 16, 0, y * 16);
                }
            }

            foreach (Chunk c in WORLDCHUNKS)
            {
                c.Update(TestShader);
            }

        }
        #endregion
        #region RAYCAST TEST
        public static bool callback(int xCopy, int yCopy, int zCopy, Vector3 face, Vector3 direction, bool active)
        {

            int cx = (int)Math.Floor(xCopy / 16f);
            int cy = (int)Math.Floor(zCopy / 16f);
            int bx = (int)mod(xCopy, 16);
            int by = (int)mod(yCopy, 128);
            int bz = (int)mod(zCopy, 16);
           // bx = xCopy % 16;
           // by = yCopy % 16;
           // bz = zCopy % 16;


            if ((bx > -1 && bx < 16) && (by > -1 && by < 128) && (bz > -1 && bz < 16))
            {
                if (WORLDCHUNKS[cx, cy].Blocks[bx, by, bz].Active)
                {
                    if (!active)
                    {
                        WORLDCHUNKS[cx, cy].Blocks[bx, by, bz].Active = false;
                        WORLDCHUNKS[cx, cy].Update(TestShader);
                    }
                    if (active)
                    {
                        if ((bx + (int)face.X > -1 && bx + (int)face.X < 16) && (by + (int)face.Y > -1 && by + (int)face.Y < 128) && (bz + (int)face.Z > -1 && bz + (int)face.Z < 16))
                        {
                            WORLDCHUNKS[cx, cy].Blocks[bx + (int)face.X, by + (int)face.Y, bz + (int)face.Z].Active = true;
                            WORLDCHUNKS[cx, cy].Blocks[bx + (int)face.X, by + (int)face.Y, bz + (int)face.Z].Color =
                                Vector3.One;
                            WORLDCHUNKS[cx, cy].Update(TestShader);
                        }
                    }
                    return true;
                }
            }
            return false;
        }
        private static float mod(float value, float modulus) // So temporary
        {
            //return value % modulus;
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
        //public static void DrawACube(Vector3 pos)
        //{
        //    GL.Begin(BeginMode.Quads);

        //    GL.Vertex3(new Vector3(0.5f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.5f, 0.0f) + pos);

        //    GL.Vertex3(new Vector3(0.0f, 0.0f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.0f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.5f, -0.5f) + pos);

        //    GL.Vertex3(new Vector3(0.5f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.0f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, 0.0f) + pos);

        //    GL.Vertex3(new Vector3(0.0f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.0f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.5f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.5f, 0.0f) + pos);

        //    GL.Vertex3(new Vector3(0.0f, 0.5f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.5f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.5f, -0.5f) + pos);

        //    GL.Vertex3(new Vector3(0.0f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.0f, 0.0f) + pos);
        //    GL.Vertex3(new Vector3(0.5f, 0.0f, -0.5f) + pos);
        //    GL.Vertex3(new Vector3(0.0f, 0.0f, -0.5f) + pos);

        //    GL.End();
        //}
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
                {
                    if (callback(x, y, z, face, direction, active))
                        break;
                }

                if (tMaxX < tMaxY)
                {
                    if (tMaxX < tMaxZ)
                    {
                        if (tMaxX > radius)
                            break;
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
                        if (tMaxZ > radius)
                            break;
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
                        if (tMaxY > radius)
                            break;
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
                        if (tMaxZ > radius)
                            break;
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


            direction = new Vector3(
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
            }
            if (Mouse.GetState().IsButtonDown(MouseButton.Right))
            {
                Raycast(direction, 8, true);
            }
            //if (Mouse.GetState().IsButtonDown(MouseButton.Right))
            //{
            //    Vector3 dirfixed = Vector3.Unproject(direction, 1280f / 2, 720f / 2, 0, 0, 0.5f, 1024f, Camera.View.Inverted());
            //    Raycast(dirfixed, 8, true);
            //    chunk.Update(TestShader);
            //}
            Window.Title = direction.ToString();
            if (Keyboard.GetState().IsKeyDown(Key.E))
            {
                tempfirst = Camera.Position;
                tempsecond = Camera.Position + direction * 8;
            }
            //Draw3DLine((int)Camera.X, (int)Camera.Y, (int)Camera.Z, (int)diradd.X, (int)diradd.Y, (int)diradd.Z);
        }
        public static NormalShader normalShader;
        public static SSAOShader SSAOShader;
        public static LinearDepthShader ldshader;
        static void Render()
        {
            GL.BindFramebuffer(FramebufferTarget.Framebuffer, NormalBuffer.FramebufferObject);
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            foreach (Chunk c in WORLDCHUNKS)
            {
                c.Mesh.Shader = normalShader;
                c.Mesh.Draw();
            }

            GL.BindFramebuffer(FramebufferTarget.Framebuffer, DepthBuffer.FramebufferObject);
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            ldshader.DepthTexture = NormalBuffer.DepthTexture;
            FramebufferMesh.Shader = ldshader;
            FramebufferMesh.Draw();

            GL.BindFramebuffer(FramebufferTarget.Framebuffer, ColorBuffer.FramebufferObject);
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);

            SSAOShader.DepthTexture = NormalBuffer.DepthTexture;
            SSAOShader.NormalTexture = NormalBuffer.ColorTexture;
            FramebufferMesh.Shader = SSAOShader;
            FramebufferMesh.Draw();
            //chunk.Mesh.Draw();
            // TestMesh.Draw();
            // GL.Begin(PrimitiveType.Lines);
            // GL.Vertex3(tempfirst);
            // GL.Vertex3(tempsecond);
            // GL.Color3(255, 0, 0);
            // GL.Color3(255, 0, 0);
            // GL.End();

            //DrawACube(new Vector3(80, 80, 80));

            GL.BindFramebuffer(FramebufferTarget.Framebuffer, FinalBuffer.FramebufferObject);
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);


            GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);
            fbshader.Texture = ColorBuffer.ColorTexture;
            FramebufferMesh.Shader = fbshader;
            FramebufferMesh.Draw();
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

            fbshader = new FramebufferShader();
            NormalBuffer = new Framebuffer(1280, 720);
            ColorBuffer = new Framebuffer(1280, 720);
            DepthBuffer = new Framebuffer(1280, 720);
            FinalBuffer = new Framebuffer(1280, 720);

            SSAOShader = new SSAOShader();
            normalShader = new NormalShader();
            ldshader = new LinearDepthShader();

            FramebufferMesh = new Mesh(new VertexData
            {
                Vertices = new float[]
                {
                    -1, -1, 0,
                    1, -1, 0,
                    1, 1, 0,
                    -1, 1, 0
                },
                TextureCoordinates = new float[]
                {
                    0, 0,
                    1, 0,
                    1, 1,
                    0, 1
                },
                Indices = new uint[]
                {
                    0, 1, 2,
                    2, 3, 0
                }

            }, new FramebufferShader()); 

            Camera = new Camera();
            Camera.Position = new Vector3(0, 128, 0);
            Camera.Yaw = 180;

            // TEMP
            TestShader = new BasicShader();

            Console.WriteLine("TESTSHADER");
            Console.WriteLine(TestShader.GetCompileStatus(ShaderType.VertexShader));
            Console.WriteLine(TestShader.GetCompileStatus(ShaderType.FragmentShader));
            Console.WriteLine(TestShader.GetCompileLog(ShaderType.VertexShader));
            Console.WriteLine(TestShader.GetCompileLog(ShaderType.FragmentShader));

            Console.WriteLine("NORMALSHADER");
            Console.WriteLine(normalShader.GetCompileStatus(ShaderType.VertexShader));
            Console.WriteLine(normalShader.GetCompileStatus(ShaderType.FragmentShader));
            Console.WriteLine(normalShader.GetCompileLog(ShaderType.VertexShader));
            Console.WriteLine(normalShader.GetCompileLog(ShaderType.FragmentShader));

            Console.WriteLine("LINEARDEPTHSHADER");
            Console.WriteLine(ldshader.GetCompileStatus(ShaderType.VertexShader));
            Console.WriteLine(ldshader.GetCompileStatus(ShaderType.FragmentShader));
            Console.WriteLine(ldshader.GetCompileLog(ShaderType.VertexShader));
            Console.WriteLine(ldshader.GetCompileLog(ShaderType.FragmentShader));

            Console.WriteLine("SSAOSHADER");
            Console.WriteLine(SSAOShader.GetCompileStatus(ShaderType.VertexShader));
            Console.WriteLine(SSAOShader.GetCompileStatus(ShaderType.FragmentShader));
            Console.WriteLine(SSAOShader.GetCompileLog(ShaderType.VertexShader));
            Console.WriteLine(SSAOShader.GetCompileLog(ShaderType.FragmentShader));

            chunk = new Chunk();
            for (int x = 0; x < 16; x += 2)
            {
                for (int y = 0; y < 128; y += 2)
                {
                    for (int z = 0; z < 16; z+= 2)
                    {
                        chunk.Blocks[x, y, z].Active = true;
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

            GenerateChunksFromThatMapYouKnow();

            //  TestMesh = new Mesh(Block.BuildCube(true, true, false, true, false, true), TestShader);
            //  TestMesh.Transform = Matrix4.CreateTranslation(22, 22, 22);

            Camera.Yaw = 90;
            // TEMP
            Vector3 posssssssss = new Vector3(141.4232f, 103.7891f, 35.3471f);
            Camera.Position = posssssssss;

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
