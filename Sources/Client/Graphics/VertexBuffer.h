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
		int vertexSize;
		MemoryHint memoryHint;
	public:
		unsigned int VertexBufferObject;

		void SetBufferData(const std::vector<float>& data, int vertexSize, MemoryHint hint);
		std::vector<float> GetBufferData();
		std::size_t GetBufferSize();
		int GetVertexSize();
		MemoryHint GetMemoryHint();

		VertexBuffer& operator=(const VertexBuffer& v);

		VertexBuffer();
		VertexBuffer(const VertexBuffer& v);
		~VertexBuffer();
	};
}