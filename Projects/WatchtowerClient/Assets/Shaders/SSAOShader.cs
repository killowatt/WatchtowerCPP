using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using WatchtowerClient.Graphics;

namespace WatchtowerClient.Assets.Shaders
{
    public class SSAOShader : Shader
    {
        // private int _modelLocation;
        // private int _viewLocation;
        private int _projectionLocation;
        private int _depthLocation;

        private int _normalLocation;
            // TODO: what if this shader moves from one mesh to the other, are these still valid? have we set that up?

        private int _kernelLocation;
        private int _noiseLocation;

        public int DepthTexture;
        public int NormalTexture;
        public int NoiseTexture;

        private Random random;

        private const int KernelSize = 16;
        private const int NoiseSize = 16;
        private Vector3[] _kernel;
        private Vector3[] _noise;

        private static Vector3[] Kernel
        {
            get
            {
                return new Vector3[]
                {
                    new Vector3(0, 0.33333333333f, -1), 
                    new Vector3(-0.28867513459f, -0.16666666666f, -1), 
                    new Vector3(0.28867513459f, -0.16666666666f, -1), 

                    new Vector3(0, 0.66666666666f, -.75f), 
                    new Vector3(-0.63403767753f, 0.20601132958f, -.75f), 
                    new Vector3(-0.39185683486f, -0.53934466291f, -.75f), 
                    new Vector3(0.39185683486f, -0.53934466291f, -.75f), 
                    new Vector3(0.63403767753f, 0.20601132958f, -.75f),

                    new Vector3(0, 1, -0.5f),
                    new Vector3(-0.70710678118f, 0.70710678118f, -0.5f), 
                    new Vector3(-1, 0, -0.5f),
                    new Vector3(-0.70710678118f, -0.70710678118f, -0.5f), 
                    new Vector3(0, -1, -0.5f),
                    new Vector3(0.70710678118f, -0.70710678118f, -0.5f), 
                    new Vector3(1, 0, -0.5f), 
                    new Vector3(0.70710678118f, 0.70710678118f, -0.5f)
                };
            }
        }

        public float Rand(float minimum, float maximum)
        {
            return (float)(random.NextDouble() * (maximum - minimum) + minimum);
        }
        public float Lerp(float a, float b, float f) // TODO: implement in a math helper? rand too
        {
            return a + f * (b - a);
        }
        public float[] VecArray(Vector3[] array) // TODO: this is probably really bad
        {
            List<float> newArray = new List<float>();
            foreach (Vector3 v in array)
            {
                newArray.Add(v.X);
                newArray.Add(v.Y);
                newArray.Add(v.Z);
            }
            return newArray.ToArray();
        }
        public override void Initialize()
        {
            random = new Random();
            _kernel = new Vector3[KernelSize];
            for (int i = 0; i < KernelSize; i++)
            {
                _kernel[i] = new Vector3(
                    Rand(-1.0f, 1.0f),
                    Rand(-1.0f, 1.0f),
                    -1.0f);
                _kernel[i] = Kernel[i];

                //_kernel[i] = new Vector3(0.0f, 0.0f, -1.0f);

                _kernel[i].Normalize();

                float scale = (float)i / KernelSize;
                scale = Lerp(0.1f, 1.0f, scale * scale);
                _kernel[i] *= scale;
            }
            //_kernel = Kernel;
            _noise = new Vector3[NoiseSize];
            for (int i = 0; i < NoiseSize; i++)
            {
                _noise[i] = new Vector3(
                    Rand(0.0f, 1.0f),
                    Rand(0.0f, 1.0f),
                    0.0f);
                //_noise[i] = new Vector3(1, 0, 0);
                _noise[i].Normalize();
            }
            _kernel[0] = new Vector3(0, 0, 1);
            int noiseTextureSize = (int)Math.Sqrt(_noise.Length);
            GL.GenTextures(1, out NoiseTexture);
            GL.BindTexture(TextureTarget.Texture2D, NoiseTexture);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter,
                (float)TextureMagFilter.Nearest);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter,
                (float)TextureMinFilter.Nearest);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb, 4, 4, 0,
                PixelFormat.Rgb, PixelType.Float, VecArray(_noise));

            //_modelLocation = GL.GetUniformLocation(ShaderProgram, "Model");
            //_viewLocation = GL.GetUniformLocation(ShaderProgram, "View");
            _projectionLocation = GL.GetUniformLocation(ShaderProgram, "Projection");
            _normalLocation = GL.GetUniformLocation(ShaderProgram, "NormalTexture");
            _depthLocation = GL.GetUniformLocation(ShaderProgram, "DepthTexture");
            _kernelLocation = GL.GetUniformLocation(ShaderProgram, "KernelSample");
            _noiseLocation = GL.GetUniformLocation(ShaderProgram, "NoiseTexture");

           // GL.UniformMatrix4(_modelLocation, false, ref Model);
            //GL.UniformMatrix4(_viewLocation, false, ref View);
            GL.UniformMatrix4(_projectionLocation, false, ref Projection);

            GL.Uniform3(_kernelLocation, KernelSize, VecArray(_kernel));

            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, NormalTexture);
            GL.Uniform1(_normalLocation, 0);
            GL.ActiveTexture(TextureUnit.Texture1);
            GL.BindTexture(TextureTarget.Texture2D, DepthTexture);
            GL.Uniform1(_depthLocation, 1);
            GL.ActiveTexture(TextureUnit.Texture2);
            GL.BindTexture(TextureTarget.Texture2D, NoiseTexture);
            GL.Uniform1(_noiseLocation, 2);
        }
        public override void Update()
        {
           // GL.UniformMatrix4(_modelLocation, false, ref Model);
            //GL.UniformMatrix4(_viewLocation, false, ref View);
            GL.UniformMatrix4(_projectionLocation, false, ref Projection);

            GL.ActiveTexture(TextureUnit.Texture0);
            GL.BindTexture(TextureTarget.Texture2D, NormalTexture);
            GL.Uniform1(_normalLocation, 0);
            GL.ActiveTexture(TextureUnit.Texture1);
            GL.BindTexture(TextureTarget.Texture2D, DepthTexture);
            GL.Uniform1(_depthLocation, 1);
        }
        public SSAOShader()
            : base(
                File.ReadAllText("Shaders/SSAO.vs"), File.ReadAllText("Shaders/SSAO.fs"),
                ShaderState.Dynamic)
        {
        }
    }
}
