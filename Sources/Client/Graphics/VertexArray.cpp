#include "VertexArray.h"
#include <GL/glew.h>
using namespace Client;

void VertexArray::AttachBuffer(VertexBuffer& buffer, int index)
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.GetVertexBufferObject());
	glVertexAttribPointer(index, buffer.GetVertexSize(), GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(index);
	glBindVertexArray(0);
}
void VertexArray::RemoveBuffer(int index)
{
	glBindVertexArray(vertexArrayObject);
	glDisableVertexAttribArray(index);
	glBindVertexArray(0);
}

unsigned int VertexArray::GetVertexArrayObject() const
{
	return vertexArrayObject;
}
void VertexArray::SetIndexBuffer(const std::vector<unsigned int>& data, MemoryHint hint)
{
	indexBuffer = data;
	indexBufferMemoryHint = hint;

	GLenum usage; // TODO: find a better solution to this without polluting everything that includes VertexBuffer.h
	if (hint == MemoryHint::Stream)
		usage = GL_STREAM_DRAW;
	else if (hint == MemoryHint::Static)
		usage = GL_STATIC_DRAW;
	else if (hint == MemoryHint::Dynamic)
		usage = GL_DYNAMIC_DRAW;
	else
		return; // TODO: exception or HANDLE IT?

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int),
		&indexBuffer[0], usage); 
	glBindVertexArray(0);
}
void VertexArray::RemoveIndexBuffer()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
}
std::vector<unsigned int> VertexArray::GetIndexBuffer() const
{
	return std::vector<unsigned int>(indexBuffer);
}
std::size_t VertexArray::GetIndexBufferSize() const
{
	return indexBuffer.size();
}
MemoryHint VertexArray::GetIndexBufferMemoryHint() const
{
	return indexBufferMemoryHint;
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &indexBufferObject);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &indexBufferObject); // OpenGL silently ignores this if it is invalid.
}