using OpenTK;
using OpenTK.Graphics;

namespace WatchtowerClient
{
    public static class Game
    {
        public static GraphicsContext Context;
        public static NativeWindow Window;

        public static bool Running;

        static void Update()
        {
        }
        static void Render()
        {
        }
        public static void Initialize(Settings settings)
        {
            Running = false;
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

            Window.Visible = true;
        }
    }
}
