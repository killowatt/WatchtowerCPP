#pragma once
#include <GL/glew.h>
#include "../../Graphics/Shader.h"
#include "../TempShaderLoader.h"

namespace Watchtower
{
	class BasicColorShader : public Shader
	{
	public:
		int modelLocation;
		int viewLocation;
		int projectionLocation;

		void Initialize();
		void Update();

		BasicColorShader(Camera& camera);
	};
}