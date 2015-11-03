#version 430
#define PI 3.14159265359

noperspective in vec2 TextureCoordinate;
vec3 ViewRay;

out vec4 color;

uniform vec3[16] KernelSample; // 16 = kernelsize

uniform sampler2D NormalTexture;
uniform sampler2D DepthTexture;
uniform sampler2D NoiseTexture;

uniform mat4 Projection;

// Settings -- Can be changed for either better performance or nicer result.
int KernelSize = 16; // 16
float Radius = 0.0005; // 0.0005 PRETTY
// Variables

void main()
{
	// HEY - SOME THINGS HERE NEED TO BE PASSED IN INSTEAD OF BEING CONSTANT
	vec2 ndc = TextureCoordinate * 2.0 - 1.0;

	float tanFoV = tan(1.57079633 / 2.0); // FOV IN RADIANS
	float aspect = 1.77777777778; // ASPECT RATIO (16 / 9)
	ViewRay = vec3(
		-ndc.x * tanFoV * aspect,
		-ndc.y * tanFoV,
		1.0);
	// END


float f = 1024.0; // YO
float n = 0.5; // PASS THESE IN
float z = (2 * n) / (f + n - texture(DepthTexture, TextureCoordinate).x * (f - n));

	vec3 origin = ViewRay * z;

	vec3 normal = texture(NormalTexture, TextureCoordinate).xyz * vec3(2.0f) - vec3(1.0f);
	normal = normalize(normal);

	vec2 noiseScale = vec2(1280 / 4, 720 / 4); // RENDER(X/Y) / NOISESIZE(sqrt length) -- THIS NEEDS TO BE PASSED IN

	vec3 rvec = texture(NoiseTexture, TextureCoordinate * noiseScale).xyz;
	vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 tbn = mat3(tangent, bitangent, normal);

	vec4 offset;

	float sampleDepth;

	float occlusion = 0.0;
	for (int i = 0; i < KernelSize; i++)
	{
		vec3 samplePosition = tbn * KernelSample[i];
		samplePosition = samplePosition * Radius + origin;

		//vec3 samplePosition = origin;

		offset = Projection * vec4(samplePosition, 1.0);
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;

		sampleDepth = (2 * n) / (f + n - texture(DepthTexture, offset.xy).x * (f - n));


		float rangeCheck = abs(origin.z - sampleDepth) < Radius ? 1.0 : 0.0;
		occlusion += (sampleDepth <= samplePosition.z ? 1.0 : 0.0) * rangeCheck;
	}
	occlusion = 1.0 - (occlusion / KernelSize);
	//color = vec4(offset.x, offset.y, 0, 1.0);
	color = vec4(occlusion, occlusion, occlusion, 1.0);
	//color = vec4(texture(NoiseTexture, TextureCoordinate).xyz, 1.0);
	//color = vec4(normal, 1.0);
	//color = vec4(origin, 1.0);
	//color = vec4(sampleDepth, sampleDepth, sampleDepth, 1.0);
	//color = vec4(offset.xy, 0.0, 1.0);
}
