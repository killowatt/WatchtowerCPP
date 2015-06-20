using System;
using System.IO;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Graphics;

namespace WatchtowerClient.Assets.Shaders
{
    public class FramebufferShader : Shader
    {
        public int Texture;
        private int _textureLocation;

        public override void Initialize()
        {
            _textureLocation = GL.GetUniformLocation(ShaderProgram, "Texture");
            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, Texture);
            GL.Uniform1(_textureLocation, 0);
        }
        public override void Update()
        {
            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, Texture);
            GL.Uniform1(_textureLocation, 0);
        }
        public FramebufferShader()
            : base(
                File.ReadAllText("Shaders/Framebuffer.vs"), File.ReadAllText("Shaders/Framebuffer.fs"),
                ShaderState.Dynamic)
        {
        }

    }
}
