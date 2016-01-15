#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameMap.h>
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "MapRenderer.h"

namespace Watchtower
{
	class Renderer
	{
	private:
		Shader* currentShader;
		Camera camera;

	public:
		void Render(const VertexArray& vertexArray);
		void Render(const VertexBuffer& vertexBuffer);

		MapRenderer mapRenderer; // TODO: temp?

		void Update();

		void SetShader(Shader& shader);
		Shader& GetShader();

		Renderer();
		Renderer(GameMap* mapPtrTemp);
		~Renderer();
	};
}