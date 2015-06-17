#version 430

in vec3 vertex;
in vec3 color;
in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Color;
out vec3 xxx;

void main()
{
	//Color = Model[3].xyz;
	Color = color;
	//Color = vertex;
	gl_Position = Projection * View * Model * vec4(vertex, 1.0);
}
