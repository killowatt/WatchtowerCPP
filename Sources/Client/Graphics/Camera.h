#pragma once
#include <glm/gtc/matrix_transform.hpp>

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
		glm::vec4 orthoSize;
		float fieldOfView;
		float zNear;
		float zFar;

		glm::mat4 GetView(); // TODO: consider performance gain for references vs potential concequences
		glm::mat4 GetProjection();
		CameraMode GetMode();
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		float GetFieldOfView();
		glm::vec2 GetAspectRatio();
		float GetZNear();
		float GetZFar();
		// get ORTHO SIZE
		
		void SetMode(CameraMode value);
		void SetPosition(glm::vec3 value); 
		void SetRotation(glm::vec3 value);
		void SetAspectRatio(glm::vec3 value);
		void SetOrthoSize(float left, float right, float bottom, float top);
		float SetFieldOfView(float value);
		float SetZNear(float value);
		float SetZFar(float value);

		Camera();
	};
}