using System;
using System.Collections.Generic;
using System.Linq;
using OpenTK;
using WatchtowerClient.Graphics;

namespace WatchtowerClient
{
    public struct Block
    {
        public bool Active;

        public static VertexData BuildCube(bool positiveX, bool negativeX, bool positiveY, bool negativeY,
            bool positiveZ, bool negativeZ)
        {
            VertexData data = new VertexData();
            List<uint> indices = new List<uint>();
            data.Vertices = new []
                {
                    0.5f, 0.5f, -0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f
                };

            #region Index
            if (positiveX)
            {
                indices.Add(0);
                indices.Add(1);
                indices.Add(2);
                indices.Add(1);
                indices.Add(2);
                indices.Add(3);
            }
            if (negativeX)
            {
                indices.Add(4);
                indices.Add(5);
                indices.Add(6);
                indices.Add(5);
                indices.Add(6);
                indices.Add(7);
            }
            if (positiveY)
            {
                indices.Add(0);
                indices.Add(1);
                indices.Add(4);
                indices.Add(1);
                indices.Add(4);
                indices.Add(5);
            }
            if (negativeY)
            {
                indices.Add(2);
                indices.Add(3);
                indices.Add(6);
                indices.Add(3);
                indices.Add(6);
                indices.Add(7);
            }
            if (positiveZ)
            {
                indices.Add(1);
                indices.Add(3);
                indices.Add(5);
                indices.Add(3);
                indices.Add(5);
                indices.Add(7);
            }
            if (negativeZ)
            {
                indices.Add(0);
                indices.Add(2);
                indices.Add(6);
                indices.Add(0);
                indices.Add(4);
                indices.Add(6);
            }
            #endregion

            data.Indices = indices.ToArray();
            return data;
        }
    }
}
