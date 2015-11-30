#include "VertexBuffer.h"
#include <GL/glew.h>

using namespace Graphics;

unsigned int VertexBuffer::GetVertexBufferObject() const 
{
	return vertexBufferObject;
}
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

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), &bufferData[0], usage);
}
std::vector<float> VertexBuffer::GetBufferData() const
{
	return std::vector<float>(bufferData); // TODO: move/copy semantics?
}
std::size_t VertexBuffer::GetBufferSize() const
{
	return bufferData.size();
}
int VertexBuffer::GetVertexSize() const
{
	return vertexSize;
}
MemoryHint VertexBuffer::GetMemoryHint() const
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
	glGenBuffers(1, &vertexBufferObject);
}
VertexBuffer::VertexBuffer(const VertexBuffer& v)
{
	glGenBuffers(1, &vertexBufferObject);
	SetBufferData(v.bufferData, v.vertexSize, v.memoryHint);
}
VertexBuffer::~VertexBuffer() // TODO: research inline some more, this and the constructor seem like good canidates.
{
	glDeleteBuffers(1, &vertexBufferObject);
}
