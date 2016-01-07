#pragma once
#include <vector>

namespace Client
{
	enum class MemoryHint
	{
		Stream,
		Static,
		Dynamic
	};
	class VertexBuffer // TODO: mark final?
	{
		std::vector<float> bufferData; // TODO: we should not hold a copy of this data!!
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

		VertexBuffer operator=(const VertexBuffer& v); // TODO: we dont really need copies do we? sets a bad precedent for resource management.
		// TODO: maybe instead, we have a method to return a shared_ptr?

		VertexBuffer();
		VertexBuffer(const VertexBuffer& v);
		~VertexBuffer();
	};
}