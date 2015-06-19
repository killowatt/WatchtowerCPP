using System;
using System.Collections.Generic;
using System.Linq;
using OpenTK;
using OpenTK.Graphics.OpenGL;
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
            List<Vector3> colors = new List<Vector3>();
            List<Vector3> normals = new List<Vector3>();
            List<uint> indices = new List<uint>();

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
            //if (positiveX)
            //{
            //    vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
            //    vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
            //    vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
                
            //    normals.Add(new Vector3(1, 0, 0));
            //    normals.Add(new Vector3(1, 0, 0));
            //    normals.Add(new Vector3(1, 0, 0));
            //    normals.Add(new Vector3(1, 0, 0));
            //}
            //if (negativeX)
            //{
            //    vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));

            //    normals.Add(new Vector3(-1, 0, 0));
            //    normals.Add(new Vector3(-1, 0, 0));
            //    normals.Add(new Vector3(-1, 0, 0));
            //    normals.Add(new Vector3(-1, 0, 0));
            //}
            //if (positiveY)
            //{
            //    vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
            //    vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));

            //    normals.Add(new Vector3(0, 1, 0));
            //    normals.Add(new Vector3(0, 1, 0));
            //    normals.Add(new Vector3(0, 1, 0));
            //    normals.Add(new Vector3(0, 1, 0));
            //}
            //if (negativeY)
            //{
            //    vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
            //    vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));

            //    normals.Add(new Vector3(0, -1, 0));
            //    normals.Add(new Vector3(0, -1, 0));
            //    normals.Add(new Vector3(0, -1, 0));
            //    normals.Add(new Vector3(0, -1, 0));
            //}
            //if (positiveZ)
            //{
            //    vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
            //    vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
            //    vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));

            //    normals.Add(new Vector3(0, 0, 1));
            //    normals.Add(new Vector3(0, 0, 1));
            //    normals.Add(new Vector3(0, 0, 1));
            //    normals.Add(new Vector3(0, 0, 1));
            //}
            //if (negativeZ)
            //{
            //    vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
            //    vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));

            //    normals.Add(new Vector3(0, 0, -1));
            //    normals.Add(new Vector3(0, 0, -1));
            //    normals.Add(new Vector3(0, 0, -1));
            //    normals.Add(new Vector3(0, 0, -1));
            //}
            #endregion

            //vertices = vertices.Distinct().ToList(); // remove dupes


            #region Experimental2
            //if (positiveX)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            //}
            //if (negativeX)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            //}
            //if (positiveY)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            //}
            //if (negativeY)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            //}
            //if (positiveZ)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, 0.5f))); // 1
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, 0.5f))); // 3
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, 0.5f))); // 5
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, 0.5f))); // 7
            //}
            //if (negativeZ)
            //{
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, -0.5f, -0.5f))); // 2
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //    indices.Add((uint)vertices.IndexOf(new Vector3(0.5f, 0.5f, -0.5f))); // 0
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, 0.5f, -0.5f))); // 4
            //    indices.Add((uint)vertices.IndexOf(new Vector3(-0.5f, -0.5f, -0.5f))); // 6
            //}
            #endregion
           
            #region Normals
            //normals = new List<Vector3>();
            ////for (int i = 0; i < indices.Count - 3; i += 3)
            ////{
            ////    Vector3 p1 = vertices[(int)indices[i]];
            ////    Vector3 p2 = vertices[(int)indices[i + 1]];
            ////    Vector3 p3 = vertices[(int)indices[i + 2]];

            ////    Vector3 U = p2 - p1;
            ////    Vector3 V = p3 - p1;

            ////    Vector3 normal = Vector3.Cross(U, V).Normalized();
            ////    normals.Insert((int)indices[i], normal);
            ////    normals.Insert((int)indices[i + 1], normal);
            ////    normals.Insert((int)indices[i + 2], normal);
            ////}
            #endregion

            #region NEW VERTEX
            if (positiveX)
            {
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));

                normals.Add(new Vector3(1, 0, 0));
                normals.Add(new Vector3(1, 0, 0));
                normals.Add(new Vector3(1, 0, 0));
                normals.Add(new Vector3(1, 0, 0));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            if (negativeX)
            {
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));

                normals.Add(new Vector3(-1, 0, 0));
                normals.Add(new Vector3(-1, 0, 0));
                normals.Add(new Vector3(-1, 0, 0));
                normals.Add(new Vector3(-1, 0, 0));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            if (positiveY)
            {
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));

                normals.Add(new Vector3(0, 1, 0));
                normals.Add(new Vector3(0, 1, 0));
                normals.Add(new Vector3(0, 1, 0));
                normals.Add(new Vector3(0, 1, 0));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            if (negativeY)
            {
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));

                normals.Add(new Vector3(0, -1, 0));
                normals.Add(new Vector3(0, -1, 0));
                normals.Add(new Vector3(0, -1, 0));
                normals.Add(new Vector3(0, -1, 0));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            if (positiveZ)
            {
                vertices.Add(new Vector3(-0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, 0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, 0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, 0.5f));

                normals.Add(new Vector3(0, 0, 1));
                normals.Add(new Vector3(0, 0, 1));
                normals.Add(new Vector3(0, 0, 1));
                normals.Add(new Vector3(0, 0, 1));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            if (negativeZ)
            {
                vertices.Add(new Vector3(-0.5f, -0.5f, -0.5f));
                vertices.Add(new Vector3(-0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, 0.5f, -0.5f));
                vertices.Add(new Vector3(0.5f, -0.5f, -0.5f));

                normals.Add(new Vector3(0, 0, -1));
                normals.Add(new Vector3(0, 0, -1));
                normals.Add(new Vector3(0, 0, -1));
                normals.Add(new Vector3(0, 0, -1));

                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 3);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 4);
                indices.Add((uint)vertices.Count - 2);
                indices.Add((uint)vertices.Count - 1);
            }
            #endregion

            foreach (Vector3 v in vertices)
            {
                colors.Add(Color);
            }

            #region OLD
            //List<Vector3> nodupe = vertices.Distinct().ToList();
            //List<float> colorexp = new List<float>();
            //List<float> normalexp = new List<float>();

            //for (int i = 0; i < vertices.Count; i++)
            //{
            //    colors.Add(Color);
            //}

            //List<float> vert = new List<float>();
            //foreach (Vector3 v in vertices)
            //{
            //    vert.Add(v.X);
            //    vert.Add(v.Y);
            //    vert.Add(v.Z);
            //}
            //foreach (Vector3 n in colors)
            //{
            //    colorexp.Add(n.X);
            //    colorexp.Add(n.Y);
            //    colorexp.Add(n.Z);
            //}
            //foreach (Vector3 n in normals)
            //{
            //    normalexp.Add(n.X);
            //    normalexp.Add(n.Y);
            //    normalexp.Add(n.Z);
            //}
            //data.Vertices = vert.ToArray();
            //data.Indices = indices.ToArray();
            //data.Colors = colorexp.ToArray();
            //data.Normals = normalexp.ToArray();
            #endregion
            
            List<float> verticesexp = new List<float>();
            List<float> normalsexp = new List<float>();
            List<float> colorexp = new List<float>();

            foreach (Vector3 v in vertices)
            {
                verticesexp.Add(v.X);
                verticesexp.Add(v.Y);
                verticesexp.Add(v.Z);
            }
            foreach (Vector3 n in normals)
            {
                normalsexp.Add(n.X);
                normalsexp.Add(n.Y);
                normalsexp.Add(n.Z);
            }
            foreach (Vector3 c in colors)
            {
                colorexp.Add(c.X);
                colorexp.Add(c.Y);
                colorexp.Add(c.Z);
            }
            data.Vertices = verticesexp.ToArray();
            data.Normals = normalsexp.ToArray();
            data.Indices = indices.ToArray();
            data.Colors = colorexp.ToArray();

            return data;
        }
        #endregion
    }
}
