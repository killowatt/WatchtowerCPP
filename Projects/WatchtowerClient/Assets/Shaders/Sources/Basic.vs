#version 430

in vec3 vertex;
in vec3 color;
in vec2 textureCoordinate;
in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Color;
out vec3 Normal;

out vec3 FragPos;

void main()
{
	Color = color;
	Normal = normal;

	FragPos = vec3(Model * vec4(vertex, 1.0f));

	gl_Position = Projection * View * Model * vec4(vertex, 1.0);
}
