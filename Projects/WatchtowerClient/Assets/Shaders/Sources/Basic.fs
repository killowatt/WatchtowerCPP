#version 430
#define PI 3.14159265359

in vec3 Color;
in vec3 Normal;

out vec4 color;

uniform vec3 cameraVector;

in vec3 FragPos;

vec3 lightDirection = vec3(0.5, -1, 0); // vector direction

void main()
{
	vec3 diffuse = max(vec3(0.0, 0.0, 0.0), dot(-lightDirection, Normal)) * Color;
	vec3 ambient = Color * 0.35;
	color = vec4(diffuse + ambient, 1.0);
}
