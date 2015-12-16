#pragma once
#include <glm/glm.hpp>
#include "Rectangle.h"

namespace Graphics
{    
	enum class CameraMode
	{
		Perspective,
		Ortho
	};
	class Camera // TODO: consider: this camera is for an fps game. do we care about quaternions?
	{
		glm::mat4 view;
		glm::mat4 projection;
		CameraMode mode;
		bool viewCalculated;
		bool projectionCalculated;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec2 aspectRatio;
		Rectangle orthoDimensions;
		float fieldOfView;
		float zNear;
		float zFar;

	public:
		glm::mat4& GetView(); // TODO: consider performance gain for references vs potential concequences
		glm::mat4& GetProjection();

		CameraMode GetMode();
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec2 GetAspectRatio();
		Rectangle GetOrthoDimensions();
		float GetFieldOfView();
		float GetZNear();
		float GetZFar();
		
		void Reset();
		void SetMode(CameraMode value);
		void SetPosition(glm::vec3 value); 
		void SetRotation(glm::vec3 value);
		void SetAspectRatio(glm::vec2 value);
		void SetOrthoDimensions(float left, float right, float top, float bottom);
		void SetOrthoDimensions(Rectangle rectangle);
		void SetFieldOfView(float value);
		void SetZNear(float value);
		void SetZFar(float value);

		Camera();
	};
}