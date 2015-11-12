#version 430

in vec3 Color;
in vec2 TextureCoordinate;

uniform sampler2D DepthTexture;

out vec4 color;

void main()
{
	float f = 1024.0; // YO
	float n = 0.5; // PASS THESE IN
	float z = (2 * n) / (f + n - texture(DepthTexture, TextureCoordinate).x * (f - n));
	color = vec4(z, z, z, 1.0);
}
