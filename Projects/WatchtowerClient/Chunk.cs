using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ExceptionServices;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Graphics;

namespace WatchtowerClient
{
    public class Chunk // TODO: clean up/finalise class~~
    {
        public Block[,,] Blocks;
        public Mesh Mesh;

        public bool Updated;

        public static readonly Vector3 ChunkSize = new Vector3(16, 128, 16);

        public void Update(Shader shader) // SHADER TEMP
        {
            VertexData chunk = new VertexData { Vertices = new float[0], Indices = new uint[0] };
            List<float> Vertices = new List<float>();
            List<float> Normals = new List<float>();
            List<uint> Indices = new List<uint>();
            VertexData block;
            int currentindoffset = 0;
            for (int x = 0; x < ChunkSize.X; x++)
            {
                for (int y = 0; y < ChunkSize.Y; y++)
                {
                    for (int z = 0; z < ChunkSize.Z; z++)
                    {
                        if (!Blocks[x, y, z].Active)
                        {
                            continue;
                        }
                        //Removes unnecessary tris.
                        bool positiveX = true;
                        if (x < ChunkSize.X - 1)
                            positiveX = !Blocks[x + 1, y, z].Active; // TODO: is this working 100%?
                        bool negativeX = true;
                        if (x > 0)
                            negativeX = !Blocks[x - 1, y, z].Active;

                        bool positiveY = true;
                        if (y < ChunkSize.Y - 1)
                            positiveY = !Blocks[x, y + 1, z].Active;
                        bool negativeY = true;
                        if (y > 0)
                            negativeY = !Blocks[x, y - 1, z].Active;

                        bool positiveZ = true;
                        if (z < ChunkSize.Z - 1)
                            positiveZ = !Blocks[x, y, z + 1].Active;
                        bool negativeZ = true;
                        if (z > 0)
                            negativeZ = !Blocks[x, y, z - 1].Active;

                        block = Block.BuildCube(positiveX, negativeX, positiveY, negativeY, positiveZ, negativeZ,
                            Blocks[x, y, z].Color);
                        //block = Block.BuildCube(true, true, true, true, true, true, Blocks[x, y, z].Color);
                        block.Translate(x, y, z);
                        block.Translate(0.5f, 0.5f, 0.5f); // fixes the problem with block problems

                        foreach (float v in block.Vertices)
                        {
                            Vertices.Add(v);
                        }
                        foreach (float n in block.Normals)
                        {
                            Normals.Add(n);
                        }
                        for (int i = 0; i < block.Indices.Length; i++)
                        {
                            Indices.Add(block.Indices[i] + (uint)currentindoffset);
                        }
                        currentindoffset += block.Vertices.Length / 3;
                    }
                }
            }

            chunk.Vertices = Vertices.ToArray();
            chunk.Normals = Normals.ToArray();
            chunk.Indices = Indices.ToArray();
            Mesh = new Mesh(chunk, shader);
            Updated = true;
        }
        public Chunk()
        {
            Blocks = new Block[(int)ChunkSize.X, (int)ChunkSize.Y, (int)ChunkSize.Z]; // TODO: stop
            for (int x = 0; x < ChunkSize.X; x++)
            {
                for (int y = 0; y < ChunkSize.Y; y++)
                {
                    for (int z = 0; z < ChunkSize.Z; z++)
                    {
                        Blocks[x, y, z] = new Block();
                        Blocks[x, y, z].Active = true;
                    }
                }
            }
            //for (int x = 0; x < ChunkSize.X; x += 4)
            //{
            //    for (int y = 0; y < ChunkSize.Y; y++)
            //    {
            //        for (int z = 0; z < ChunkSize.Z; z++)
            //        {
            //            Blocks[x, y, z].Active = true;
            //        }
            //    }
            //}
        }
    }
}
