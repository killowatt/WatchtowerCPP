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
        public static void Initialize()
        {
            Running = false;
            Window = new NativeWindow();
        }
    }
}
