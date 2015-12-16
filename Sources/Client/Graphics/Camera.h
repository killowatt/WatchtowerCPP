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
		float fieldOfView;
		float zNear;
		float zFar;
		bool orthoDepthEnabled;
		Rectangle orthoDimensions;

	public:
	    glm::mat4& GetView(); // TODO: consider somehow making these const? is it beneficial?
		glm::mat4& GetProjection();

		CameraMode GetMode() const;
		glm::vec3 GetPosition() const;
		glm::vec3 GetRotation() const;
		glm::vec2 GetAspectRatio() const;
		float GetFieldOfView() const;
		float GetZNear() const;
		float GetZFar() const;
		bool GetOrthoDepthEnabled() const;
		Rectangle GetOrthoDimensions() const;
		
		void Reset(); // TODO: potentially remove since we no longer use value return for view/pr. ALTHO WE DONT HAVE CONST REFERENCE
		void Calculate();
		void SetMode(CameraMode value);
		void SetPosition(glm::vec3 value);
		void SetPositionX(float value);
		void SetPositionY(float value);
		void SetPositionZ(float value);
		void SetRotation(glm::vec3 value);
		void SetRotationX(float value);
		void SetRotationY(float value);
		void SetRotationZ(float value);
		void SetAspectRatio(glm::vec2 value);
		void SetFieldOfView(float value);
		void SetZNear(float value);
		void SetZFar(float value);
		void SetOrthoDepthEnabled(bool value);
		void SetOrthoDimensions(float left, float right, float top, float bottom);
		void SetOrthoDimensions(Rectangle rectangle);

		Camera();
	};
}