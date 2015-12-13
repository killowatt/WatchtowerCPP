#pragma once
#include "VertexBuffer.h"
#include <vector>
#include <map>

namespace Graphics
{
	class VertexArray
	{
		unsigned int vertexArrayObject;
		unsigned int indexBufferObject;
		
		std::vector<unsigned int> indexBuffer;
	public:
		void AttachBuffer(VertexBuffer& buffer, int index);
		void RemoveBuffer(int index);

		void SetIndexBuffer(const std::vector<unsigned int>& data);
		void RemoveIndexBuffer();
		std::vector<unsigned int> GetIndexBuffer() const;
		std::size_t GetIndexBufferSize() const;

		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray();
		VertexArray(const VertexArray&) = delete;
		~VertexArray();
	};
}