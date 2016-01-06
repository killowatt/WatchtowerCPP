#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace Client;

void Camera::Update()
{
	Direction = glm::vec3(
		cos(Rotation.y) * sin(Rotation.x),
		sin(Rotation.y),
		cos(Rotation.y) * cos(Rotation.x));

	Right = glm::vec3(
		sin(Rotation.x - 3.14f / 2.0f),
		0,
		cos(Rotation.x - 3.14f / 2.0f));

	Up = glm::cross(Right, Direction);

	View = glm::lookAt(Position, Position + Direction, Up);

	if (Mode == CameraMode::Perspective)
		Projection = glm::perspective(FieldOfView, AspectRatio.x / AspectRatio.y, ZNear, ZFar);
	else if (Mode == CameraMode::Ortho)
	{
		if (OrthoDepthEnabled == false)
			Projection = glm::ortho(
				OrthoDimensions.Left, OrthoDimensions.Right,
				OrthoDimensions.Bottom, OrthoDimensions.Top);
		else
			Projection = glm::ortho(
				OrthoDimensions.Left, OrthoDimensions.Right,
				OrthoDimensions.Bottom, OrthoDimensions.Top,
				ZNear, ZFar);
	}
}

Camera::Camera()
{
	Mode = CameraMode::Perspective;
	Position = glm::vec3();
	Rotation = glm::vec2();
	AspectRatio = glm::vec2(16, 9);
	FieldOfView = 1.5708f;
	ZNear = 0.1f;
	ZFar = 8192;
	OrthoDepthEnabled = true;
	OrthoDimensions = Common::Rectangle(-128, 128, 128, -128);
}
