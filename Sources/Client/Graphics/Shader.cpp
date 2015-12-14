#include "Shader.h"
#include <GL/glew.h>

using namespace Graphics;
                                        // TODO: canidate for inline probs
unsigned int Shader::GetProgram() const // TODO: evaluate the speed of these methods vs having public fields.
{
	return shaderProgram;
}
unsigned int Shader::GetShader(ShaderType type) const
{
	if (type == ShaderType::Vertex)
		return vertexShader;
	else if (type == ShaderType::Fragment)
		return fragmentShader;
	return 0;
}

bool Shader::GetCompileStatus(ShaderType type) const
{
	int result = 0;
	if (type == ShaderType::Vertex)
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	else if (type == ShaderType::Fragment)
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	else
		return false;
	return result != 0;
}

std::string Shader::GetCompileLog(ShaderType type) const
{
	int logLength = 0;

	if (type == ShaderType::Vertex)
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	else if (type == ShaderType::Fragment)
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	else
		return std::string("The shader type defined was invalid.");

	if (logLength > 0)
	{
		char* logBuffer = new char[logLength];
		if (type == ShaderType::Vertex)
			glGetShaderInfoLog(vertexShader, logLength, nullptr, logBuffer);
		else if (type == ShaderType::Fragment)
			glGetShaderInfoLog(fragmentShader, logLength, nullptr, logBuffer);

		std::string log(logBuffer);
		delete logBuffer;
		return log;
	}
	return std::string("The shader reported no errors or warnings.");
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, ShaderState state)
	: Shader::Shader(vertexSource.c_str(), fragmentSource.c_str(), state) {} // TODO: are these c_str pointers actually safe even with references?

Shader::Shader(const char* vertexSource, const char* fragmentSource, ShaderState state)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
}
Shader::~Shader()
{
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(shaderProgram);
}


