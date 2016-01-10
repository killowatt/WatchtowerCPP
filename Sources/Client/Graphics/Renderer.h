#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameMap.h>
#include "VertexArray.h"
#include "Shader.h"
#include "MapRenderer.h"

namespace Client
{
	class Renderer
	{
	private:
		Shader* currentShader;

	public:
		void Render(const VertexArray& vertexArray);
		void Render(const VertexBuffer& vertexBuffer);

		MapRenderer mapRenderer; // TODO: temp?

		void Update();

		void SetShader(Shader& shader);
		Shader& GetShader();

		Renderer();
		Renderer(Common::GameMap* mapPtrTemp);
		~Renderer();
	};
}