using System;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace WatchtowerClient.Graphics
{
    public class Mesh
    {
        internal VertexArray VertexArray;
        public Shader Shader;

        public Matrix4 Transform;

        public VertexData VertexData
        {
            get { return VertexArray.VertexData; }
            set { VertexArray.VertexData = value; }
        }
        public Mesh Copy() 
        {
            return (Mesh)MemberwiseClone();
        }
        public void Draw()
        {
            GL.BindVertexArray(VertexArray.VertexArrayObject);
            GL.UseProgram(Shader.ShaderProgram);

            if (!Shader.Initialized || Shader.State == ShaderState.Dynamic)
            {
                Shader.Model = Transform;
                Shader.View = Game.Camera.View; // TODO: replace
                Shader.Projection = Game.Camera.Projection;
            }
            if (!Shader.Initialized)
            {
                Shader.Initialize();
                Shader.Initialized = true;
            }
            if (Shader.State == ShaderState.Dynamic)
            {
                Shader.Update();
            }

            GL.DrawElements(PrimitiveType.Triangles, VertexData.Indices.Length, DrawElementsType.UnsignedInt, IntPtr.Zero);
        }
        public Mesh(VertexData vertexData, Shader shader)
        {
            VertexArray = new VertexArray(vertexData);
            Shader = shader;
            Transform = Matrix4.Identity;
        }
    }
}
