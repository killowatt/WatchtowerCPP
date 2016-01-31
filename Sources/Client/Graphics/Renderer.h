#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "VertexArray.h"
#include "Shader.h"
#include <GameMap.h>

namespace Watchtower
{
	class Client;
	class Renderer
	{
	private:
		struct RenderChunk
		{
			VertexArray VertexArray;
			VertexBuffer Vertices;
			VertexBuffer Colors;
			VertexBuffer Normals;
			glm::mat4 Transform;

			void Generate(Chunk& chunk, unsigned int x, unsigned int y); // TODO:
		};

		Camera camera;
		Shader* shader;
		
		GameMap* map; // TODO: reconsider
		RenderChunk* chunks;

	public:
		void Render(const VertexArray& vertexArray);
		void RenderWorld();

		void UpdateChunk(unsigned int x, unsigned int y);
		void UpdateWorld();

		void SetCamera(Camera camera);
		Camera& GetCamera();

		void SetShader(Shader& shader);
		Shader& GetShader();

		Renderer(GameMap* map);
		~Renderer();
	};
}