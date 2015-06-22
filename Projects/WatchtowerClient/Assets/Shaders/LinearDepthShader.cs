using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Graphics;

namespace WatchtowerClient.Assets.Shaders
{
    public class LinearDepthShader : Shader
    {
        private int _depthLocation;

        public int DepthTexture;

        public override void Initialize()
        {
            _depthLocation = GL.GetUniformLocation(ShaderProgram, "DepthTexture");

            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, DepthTexture);
            GL.Uniform1(_depthLocation, 0);
        }
        public override void Update()
        {
            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, DepthTexture);
            GL.Uniform1(_depthLocation, 0);
        }
        public LinearDepthShader()
            : base(
                File.ReadAllText("Shaders/LinearDepth.vs"), File.ReadAllText("Shaders/LinearDepth.fs"),
                ShaderState.Dynamic)
        {
        }
    }
}
