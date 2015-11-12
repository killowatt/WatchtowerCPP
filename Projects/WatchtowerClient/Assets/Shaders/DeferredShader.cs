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
    public class DeferredShader : Shader
    {
        private int _modelLocation;
        private int _viewLocation;
        private int _projectionLocation;

        public override void Initialize()
        {
            _modelLocation = GL.GetUniformLocation(ShaderProgram, "Model");
            _viewLocation = GL.GetUniformLocation(ShaderProgram, "View");
            _projectionLocation = GL.GetUniformLocation(ShaderProgram, "Projection");

            GL.UniformMatrix4(_modelLocation, false, ref Model);
            GL.UniformMatrix4(_viewLocation, false, ref View);
            GL.UniformMatrix4(_projectionLocation, false, ref Projection);
        }
        public override void Update()
        {
            GL.UniformMatrix4(_modelLocation, false, ref Model);
            GL.UniformMatrix4(_viewLocation, false, ref View);
            GL.UniformMatrix4(_projectionLocation, false, ref Projection);
        }
        public DeferredShader()
            : base(
                File.ReadAllText("Shaders/Final.vs"), File.ReadAllText("Shaders/Final.fs"),
                ShaderState.Dynamic)
        {
        }
    }
}
