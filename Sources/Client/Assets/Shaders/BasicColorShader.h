#pragma once
#include <GL/glew.h>
#include "../../Graphics/Shader.h"
#include "../TempShaderLoader.h"

namespace Client
{
	class BasicColorShader : public Client::Shader
	{
	public:
		int modelLocation;
		int viewLocation;
		int projectionLocation;

		void Initialize();
		void Update();

		BasicColorShader(Client::Camera& camera);
	};
}