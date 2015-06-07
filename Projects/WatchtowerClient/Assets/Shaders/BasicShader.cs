using System;
using System.IO;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Graphics;

namespace WatchtowerClient.Assets.Shaders
{
    public class BasicShader : Shader
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
            GL.UniformMatrix4(_modelLocation, false, ref Model); // TODO: is this necessary for matrices? because ref
            GL.UniformMatrix4(_viewLocation, false, ref View);
            GL.UniformMatrix4(_projectionLocation, false, ref Projection);
        }
        public BasicShader()
            : base(
                File.ReadAllText("Shaders/3DBasicVertex.glsl"), File.ReadAllText("Shaders/3DBasicFragment.glsl"),
                ShaderState.Dynamic)
        {
        }
    }
}
