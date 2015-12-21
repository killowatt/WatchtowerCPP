#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;

out vec3 color;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    //vec3 Normal = mat3(Model * View) * normal;
    color = normal;
    gl_Position = Projection * View * Model * vec4(vertex, 1.0);
}
