#version 430

in vec2 TextureCoordinate;
out vec4 color;

uniform sampler2D Texture;

void main()
{
	color = texture2D(Texture, TextureCoordinate);
}
