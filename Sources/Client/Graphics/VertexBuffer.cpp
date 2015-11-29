#include "VertexBuffer.h"
#include <GL/glew.h>

using namespace Graphics;

void VertexBuffer::SetBufferData(const std::vector<float>& data, int vertSize, MemoryHint hint)
{
	bufferData = data;
	vertexSize = vertSize;
	memoryHint = hint;

	GLenum usage; // TODO: find a better solution to this without polluting everything that includes VertexBuffer.h
	switch (hint)
	{
	case MemoryHint::Stream:
		usage = GL_STREAM_DRAW;
		break;
	case MemoryHint::Static:
		usage = GL_STATIC_DRAW;
		break;
	case MemoryHint::Dynamic:
		usage = GL_DYNAMIC_DRAW;
		break;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), &bufferData[0], usage);
}
std::vector<float> VertexBuffer::GetBufferData()
{
	return std::vector<float>(bufferData); // todo: move/copy semantics?
}
std::size_t VertexBuffer::GetBufferSize()
{
	return bufferData.size();
}
int VertexBuffer::GetVertexSize()
{
	return vertexSize;
}
MemoryHint VertexBuffer::GetMemoryHint()
{
	return memoryHint;
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& v)
{
	VertexBuffer* buffer = new VertexBuffer();
	buffer->SetBufferData(v.bufferData, v.vertexSize, v.memoryHint);
	return *buffer;
}

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &VertexBufferObject);
}
VertexBuffer::VertexBuffer(const VertexBuffer& v)
{
	glGenBuffers(1, &VertexBufferObject);
	SetBufferData(v.bufferData, v.vertexSize, v.memoryHint);
}
VertexBuffer::~VertexBuffer() // TODO: research inline some more, this and the constructor seem like good canidates.
{
	glDeleteBuffers(1, &VertexBufferObject);
}
