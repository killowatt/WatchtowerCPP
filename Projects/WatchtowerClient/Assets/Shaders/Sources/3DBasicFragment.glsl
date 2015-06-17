#version 430

in vec3 Color;
in vec3 xxx;

out vec4 color;

void main()
{
	color = vec4(Color.x / 16, Color.y / 128, Color.z / 16, 1.0);
    //color = vec4(xxx.x / 16, xxx.y / 128, xxx.z / 16, 1.0);
    color = vec4(Color, 1.0);
}
