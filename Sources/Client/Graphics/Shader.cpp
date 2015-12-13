#include "Shader.h"
#include <GL/glew.h>

using namespace Graphics;

bool Shader::GetCompileStatus(ShaderType type)
{
	int result = 0;
	if (type == ShaderType::Vertex)
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (type == ShaderType::Fragment)
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	else
		return false;
	return result != 0;
}

std::string Shader::GetCompileLog(ShaderType type)
{
	int logLength = 0;

	if (type == ShaderType::Vertex)
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	if (type == ShaderType::Fragment)
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	else
		return std::string("The shader type defined was invalid.");

	if (logLength > 0)
	{
		char* logBuffer = new char[logLength];
		if (type == ShaderType::Vertex)
			glGetShaderInfoLog(vertexShader, logLength, nullptr, logBuffer);
		if (type == ShaderType::Fragment)
			glGetShaderInfoLog(fragmentShader, logLength, nullptr, logBuffer);

		std::string log(logBuffer);
		delete logBuffer;
		return log;
	}
	else
		return std::string("The shader reported no errors or warnings.");
}

Shader::Shader(std::string vertexSource, std::string fragmentSource)
	: Shader::Shader(vertexSource.c_str(), fragmentSource.c_str()) {}

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
}
Shader::~Shader()
{
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(shaderProgram);
}


