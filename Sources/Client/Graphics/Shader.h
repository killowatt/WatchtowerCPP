#pragma once
#include <glm/mat4x4.hpp>
#include <string>

namespace Graphics
{
	enum class ShaderState
	{
		Static,
		Dynamic
	};
	enum class ShaderType
	{
		Vertex,
		Fragment
	};
	class Shader
	{
		unsigned int shaderProgram;
		unsigned int vertexShader;
		unsigned int fragmentShader;

	public:
		ShaderState State;

		glm::mat4 Model;
		glm::mat4 View;
		glm::mat4 Projection;

		bool GetCompileStatus(ShaderType type);
		std::string GetCompileLog(ShaderType type);

		virtual void Initialize() = 0;
		virtual void Update() = 0;

	protected:
		Shader() = delete;
		Shader(std::string vertexSource, std::string fragmentSource);
		Shader(const char* vertexSource, const char* fragmentSource);
	public:
		~Shader();
	};
}