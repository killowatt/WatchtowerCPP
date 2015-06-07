using System;
using System.Collections.Generic;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace WatchtowerClient.Graphics
{
    public enum ShaderState
    {
        Static,
        Dynamic
    }
    public abstract class Shader
    {
        internal int ShaderProgram;
        internal int VertexShader;
        internal int FragmentShader;

        public ShaderState State;
        internal bool Initialized;

        protected internal Matrix4 Model; // These are updated during rendering for use during update.
        protected internal Matrix4 View;
        protected internal Matrix4 Projection;

        public abstract void Initialize();
        public abstract void Update();

        public bool GetCompileStatus(ShaderType type)
        {
            int status = 0;
            if (type == ShaderType.VertexShader)
            {
                GL.GetShader(VertexShader, ShaderParameter.CompileStatus, out status);
            }
            else if (type == ShaderType.FragmentShader)
            {
                GL.GetShader(FragmentShader, ShaderParameter.CompileStatus, out status);
            }

            switch (status)
            {
                case 0:
                    return false;
                case 1:
                    return true;
                default:
                    return false;
            }
        }
        public string GetCompileLog(ShaderType type)
        {
            if (type == ShaderType.FragmentShader)
            {
                return GL.GetShaderInfoLog(FragmentShader);
            }
            if (type == ShaderType.VertexShader)
            {
                return GL.GetShaderInfoLog(VertexShader);
            }
            return String.Empty; // TODO: error?
        }

        public Shader(string vertexSource, string fragmentSource, ShaderState state)
        {
            State = state;
            Initialized = false;

            VertexShader = GL.CreateShader(ShaderType.VertexShader);
            GL.ShaderSource(VertexShader, vertexSource);
            GL.CompileShader(VertexShader);

            FragmentShader = GL.CreateShader(OpenTK.Graphics.OpenGL.ShaderType.FragmentShader);
            GL.ShaderSource(FragmentShader, fragmentSource);
            GL.CompileShader(FragmentShader);

            ShaderProgram = GL.CreateProgram();
            GL.AttachShader(ShaderProgram, VertexShader);
            GL.AttachShader(ShaderProgram, FragmentShader);

            GL.BindAttribLocation(ShaderProgram, 0, "vertex");
            GL.BindAttribLocation(ShaderProgram, 1, "textureCoordinate");
            GL.BindAttribLocation(ShaderProgram, 2, "normal");

            GL.LinkProgram(ShaderProgram);
        }
    }
}
