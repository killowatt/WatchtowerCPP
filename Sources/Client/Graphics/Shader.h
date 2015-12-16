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
	protected:
		unsigned int shaderProgram;
		unsigned int vertexShader;
		unsigned int fragmentShader;

	public:
		ShaderState State;

		glm::mat4& Model;
		glm::mat4& View;
		glm::mat4& Projection;

		unsigned int GetProgram() const;
		unsigned int GetShader(ShaderType type) const;

		bool GetCompileStatus(ShaderType type) const;
		std::string GetCompileLog(ShaderType type) const;

		virtual void Initialize() = 0; // TODO: should these be () const = 0;? probably?
		virtual void Update() = 0;

	protected:
		Shader() = delete;
		Shader(const std::string& vertexSource, const std::string& fragmentSource,
			ShaderState state);
		Shader(const char* vertexSource, const char* fragmentSource, ShaderState state);
	public:
		~Shader();
	};
}