#version 430

in vec3 Color;
in vec3 Normal;

out vec4 color;

void main()
{
	color = vec4(Normal, 1.0);
}
