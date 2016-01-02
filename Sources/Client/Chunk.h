#pragma once

#include <glm/glm.hpp>
#include <Chunk.h>
#include "Block.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"

class Chunk : public Common::Chunk
{
public:
	glm::mat4 Transform;

	Graphics::VertexArray VertexArray;
	Graphics::VertexBuffer Vertices;
	Graphics::VertexBuffer Colors;
	Graphics::VertexBuffer Normals;

	void Update();

	Chunk();
	~Chunk();
};