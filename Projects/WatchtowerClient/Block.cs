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
        public Vector3 Color;

        #region BuildCube(Nasty)
        public static VertexData BuildCube(bool positiveX, bool negativeX, bool positiveY, bool negativeY,
            bool positiveZ, bool negativeZ, Vector3 Color)
        {
            VertexData data = new VertexData();
            List<uint> indices = new List<uint>();
            data.Vertices = new[]
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
            List<Vector3> vertices = new List<Vector3>();
            List<Vector3> normals = new List<Vector3>();

            #region Index
            //if (positiveX)
            //{
            //    indices.Add(0);
            //    indices.Add(1);
            //    indices.Add(2);
            //    indices.Add(1);
            //    indices.Add(2);
            //    indices.Add(3);
            //}
            //if (negativeX)
            //{
            //    indices.Add(4);
            //    indices.Add(5);
            //    indices.Add(6);
            //    indices.Add(5);
            //    indices.Add(6);
            //    indices.Add(7);
            //}
            //if (positiveY)
            //{
            //    indices.Add(0);
            //    indices.Add(1);
            //    indices.Add(4);
            //    indices.Add(1);
            //    indices.Add(4);
            //    indices.Add(5);
            //}
            //if (negativeY)
            //{
            //    indices.Add(2);
            //    indices.Add(3);
            //    indices.Add(6);
            //    indices.Add(3);
            //    indices.Add(6);
            //    indices.Add(7);
            //}
            //if (positiveZ)
            //{
            //    indices.Add(1);
            //    indices.Add(3);
            //    indices.Add(5);
            //    indices.Add(3);
            //    indices.Add(5);
            //    indices.Add(7);
            //}
            //if (negativeZ)
            //{
            //    indices.Add(0);
            //    indices.Add(2);
            //    indices.Add(6);
            //    indices.Add(0);
            //    indices.Add(4);
            //    indices.Add(6);
            //}
            #endregion

            #region Experimental
            if (positiveX)
            {
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
            }
            if (negativeX)
            {
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));
            }
            if (positiveY)
            {
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
            }
            if (negativeY)
            {
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));
            }
            if (positiveZ)
            {
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));
            }
            if (negativeZ)
            {
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
            }
            #endregion

            vertices = vertices.Distinct().ToList(); // remove dupes

            #region Experimental2
            if (positiveX)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            }
            if (negativeX)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            }
            if (positiveY)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            }
            if (negativeY)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            }
            if (positiveZ)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            }
            if (negativeZ)
            {
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
                indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
                indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            }
            #endregion

            //List<Vector3> nodupe = vertices.Distinct().ToList();
            List<float> denorms = new List<float>();

            for (int i = 0; i < vertices.Count; i++)
            {
                normals.Add(Color);
            }

            List<float> vert = new List<float>();
            foreach (Vector3 v in vertices)
            {
                vert.Add(v.X);
                vert.Add(v.Y);
                vert.Add(v.Z);
            }
            foreach (Vector3 n in normals)
            {
                denorms.Add(n.X);
                denorms.Add(n.Y);
                denorms.Add(n.Z);
            }
            data.Vertices = vert.ToArray();
            data.Indices = indices.ToArray();
            data.Normals = denorms.ToArray();
            
            return data;
        }
        #endregion
    }
}
