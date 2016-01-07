#pragma once
#include "VertexBuffer.h"
#include <vector>

namespace Client
{
	class VertexArray
	{
		unsigned int vertexArrayObject;
		unsigned int indexBufferObject;

		std::vector<unsigned int> indexBuffer;
		MemoryHint indexBufferMemoryHint;
	public:
		void AttachBuffer(VertexBuffer& buffer, int index);
		void RemoveBuffer(int index);

		unsigned int GetVertexArrayObject() const;
		void SetIndexBuffer(const std::vector<unsigned int>& data, MemoryHint hint);
		void RemoveIndexBuffer();
		std::vector<unsigned int> GetIndexBuffer() const;
		std::size_t GetIndexBufferSize() const;
		MemoryHint GetIndexBufferMemoryHint() const;

		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray();
		VertexArray(const VertexArray&) = delete;
		~VertexArray();
	};
}