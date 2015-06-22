#version 430

in vec3 vertex;
in vec2 textureCoordinate;

out vec2 TextureCoordinate;

void main()
{
	TextureCoordinate = textureCoordinate;
	gl_Position = vec4(vertex, 1.0);
}
