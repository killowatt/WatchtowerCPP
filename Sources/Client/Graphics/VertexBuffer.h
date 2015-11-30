#pragma once
#include <vector>

namespace Graphics
{
	enum class MemoryHint
	{
		Stream,
		Static,
		Dynamic
	};
	class VertexBuffer
	{
		std::vector<float> bufferData;
		unsigned int vertexBufferObject;
		int vertexSize;
		MemoryHint memoryHint;

	public:
		unsigned int GetVertexBufferObject() const; // We use const for methods that don't change the object.

		void SetBufferData(const std::vector<float>& data, int vertexSize, MemoryHint hint);
		std::vector<float> GetBufferData() const;
		std::size_t GetBufferSize() const;
		int GetVertexSize() const;
		MemoryHint GetMemoryHint() const;

		VertexBuffer& operator=(const VertexBuffer& v); // TODO: we dont really need copies do we? sets a bad precedent for resource management.

		VertexBuffer();
		VertexBuffer(const VertexBuffer& v);
		~VertexBuffer();
	};
}