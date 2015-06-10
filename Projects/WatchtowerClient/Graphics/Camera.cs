
using OpenTK;

namespace WatchtowerClient.Graphics
{
    public static class Camera
    {
        public static float x = 0;
        // Temp camera
        public static Matrix4 Projection = Matrix4.CreatePerspectiveFieldOfView(1.57079633f, 16f / 9f, 0.5f, 1024);
        public static Matrix4 View = Matrix4.LookAt(64, 64, 64, 8, 64, 8, 0, 1, 0);
        public static void Update()
        {
            View = View * Matrix4.CreateRotationY(x);
            x++;
        }
    }
}
