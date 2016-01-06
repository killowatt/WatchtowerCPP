#pragma once
#include <glm/glm.hpp>
#include <Graphics/Rectangle.h>

namespace Client
{
	enum class CameraMode
	{
		Perspective,
		Ortho
	};
	class Camera // TODO:  this camera is for an fps game. do we care about quaternions?
	{
	public:
		glm::mat4 View;
		glm::mat4 Projection;
		CameraMode Mode;

		glm::vec3 Position;
		glm::vec2 Rotation;

		glm::vec3 Direction;
		glm::vec3 Right;
		glm::vec3 Up;

		glm::vec2 AspectRatio;
		float FieldOfView;
		float ZNear;
		float ZFar;

		bool OrthoDepthEnabled;
		Common::Rectangle OrthoDimensions;

		void Update();

		Camera();
	};
}

