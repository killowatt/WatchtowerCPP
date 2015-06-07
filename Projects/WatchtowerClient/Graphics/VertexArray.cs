using System;
using OpenTK.Graphics.OpenGL;

namespace WatchtowerClient.Graphics
{
    internal struct VertexData
    {
        public float[] Vertices;
        public float[] TextureCoordinates;
        public float[] Normals;
        public uint[] Indices;
    }
    internal sealed class VertexArray
    {
        internal readonly int VertexArrayObject;
        private VertexData _vertexData;
        private int _vertexBuffer;
        private int _textureCoordinateBuffer;
        private int _normalBuffer;
        private int _indexBuffer;

        public float[] Vertices // TODO: ONLY SETUP VERTEX ATTRIB IF DATA EXISTS?
        {
            get { return _vertexData.Vertices; }
            set
            {
                if (value == null)
                    value = new float[0];
                _vertexData.Vertices = value;
                GL.BindVertexArray(VertexArrayObject);
                GL.BindBuffer(BufferTarget.ArrayBuffer, _vertexBuffer);
                GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(sizeof (float) * _vertexData.Vertices.Length),
                    _vertexData.Vertices, BufferUsageHint.DynamicDraw);
                GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 0, 0);
                GL.EnableVertexAttribArray(0);
                GL.BindVertexArray(0);
            }
        }
        public float[] TextureCoordinates
        {
            get { return _vertexData.TextureCoordinates; }
            set
            {
                if (value == null)
                    value = new float[0];
                _vertexData.TextureCoordinates = value;
                GL.BindVertexArray(VertexArrayObject);
                GL.BindBuffer(BufferTarget.ArrayBuffer, _textureCoordinateBuffer);
                GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(sizeof (float) * _vertexData.TextureCoordinates.Length),
                    _vertexData.TextureCoordinates, BufferUsageHint.DynamicDraw);
                GL.VertexAttribPointer(1, 2, VertexAttribPointerType.Float, false, 0, 0);
                GL.EnableVertexAttribArray(1);
                GL.BindVertexArray(0);
            }
        }
        public float[] Normals
        {
            get { return _vertexData.Normals; }
            set
            {
                if (value == null)
                    value = new float[0];
                _vertexData.Normals = value;
                GL.BindVertexArray(VertexArrayObject);
                GL.BindBuffer(BufferTarget.ArrayBuffer, _normalBuffer);
                GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(sizeof (float) * _vertexData.Normals.Length), _vertexData.Normals,
                    BufferUsageHint.DynamicDraw);
                GL.VertexAttribPointer(2, 3, VertexAttribPointerType.Float, false, 0, 0);
                GL.EnableVertexAttribArray(2);
                GL.BindVertexArray(0);
            }
        }
        public uint[] Indices
        {
            get { return _vertexData.Indices; }
            set
            {
                if (value == null)
                    value = new uint[0];
                _vertexData.Indices = value;
                GL.BindVertexArray(VertexArrayObject);
                GL.BindBuffer(BufferTarget.ElementArrayBuffer, _indexBuffer);
                GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(sizeof (uint) * _vertexData.Indices.Length),
                    _vertexData.Indices,
                    BufferUsageHint.DynamicDraw);
                GL.BindVertexArray(0);
            }
        }
        public VertexData VertexData
        {
            get { return _vertexData; }
            set
            {
                _vertexData = value;
                Vertices = _vertexData.Vertices;
                TextureCoordinates = _vertexData.TextureCoordinates;
                Normals = _vertexData.Normals;
                Indices = _vertexData.Indices;
            }
        }
        internal VertexArray(VertexData vertexData)
        {
            GL.GenVertexArrays(1, out VertexArrayObject);
            GL.BindVertexArray(VertexArrayObject);

            GL.GenBuffers(1, out _vertexBuffer);
            GL.GenBuffers(1, out _textureCoordinateBuffer);
            GL.GenBuffers(1, out _normalBuffer);
            GL.GenBuffers(1, out _indexBuffer);

            VertexData = vertexData;

            GL.BindVertexArray(0);
        }

    }
}
