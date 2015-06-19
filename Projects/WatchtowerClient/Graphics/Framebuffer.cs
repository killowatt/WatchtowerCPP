using System;
using OpenTK.Graphics.OpenGL;

namespace WatchtowerClient.Graphics
{
    public class Framebuffer
    {
        internal int FramebufferObject;
        public int ColorTexture;
        public int DepthTexture;

        public Mesh FramebufferMesh;

        public Framebuffer(int width, int height, Shader shader)
        {
            FramebufferMesh = new Mesh(new VertexData
                {
                    Vertices = new float[]
                    { 
                    -1, -1, 0,
                    1, -1, 0,
                    1, 1, 0,
                    -1, 1, 0
                    },


                }, shader);

            GL.GenTextures(1, out ColorTexture);
            GL.GenTextures(1, out DepthTexture);
            GL.GenFramebuffers(1, out FramebufferObject);

            GL.BindTexture(TextureTarget.Texture2D, ColorTexture);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb, width, height, 0, PixelFormat.Rgb, PixelType.UnsignedByte, IntPtr.Zero);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (float)TextureMagFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (float)TextureMinFilter.Linear);
            GL.FramebufferTexture2D(FramebufferTarget.Framebuffer, FramebufferAttachment.ColorAttachment0, TextureTarget.Texture2D, ColorTexture, 0);

            GL.BindTexture(TextureTarget.Texture2D, DepthTexture);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.DepthComponent24, width, height, 0, PixelFormat.DepthComponent, PixelType.UnsignedByte, IntPtr.Zero);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (float)TextureMagFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (float)TextureMinFilter.Linear);
            GL.FramebufferTexture2D(FramebufferTarget.Framebuffer, FramebufferAttachment.DepthAttachment, TextureTarget.Texture2D, DepthTexture, 0);

            GL.BindTexture(TextureTarget.Texture2D, 0);
            GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
        }
    }
}
