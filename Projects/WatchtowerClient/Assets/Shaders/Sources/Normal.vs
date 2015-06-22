#version 430

in vec3 vertex;
in vec3 color;
in vec2 textureCoordinate;
in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Normal;

void main()
{
	Normal = mat3(Model * View) * normal;
	gl_Position = Projection * View * Model * vec4(vertex, 1.0);
}
