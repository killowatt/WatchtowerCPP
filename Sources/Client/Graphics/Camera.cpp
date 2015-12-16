#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Graphics;

glm::mat4& Camera::GetView()
{
	if (!viewCalculated)
	{
		glm::vec3 direction = glm::vec3(
			cos(rotation.z) * sin(rotation.y),
			sin(rotation.z),
			cos(rotation.z) * cos(rotation.y));

		glm::vec3 right = glm::vec3(
			sin(rotation.y - 3.14f / 2.0f),
			0,
			cos(rotation.y - 3.14f / 2.0f));

		glm::vec3 up = glm::cross(right, direction);

		view = glm::lookAt(position, position + direction, up);
		viewCalculated = true;
	}
	return view;
}
glm::mat4& Camera::GetProjection() // TODO: Make reference for speed?
{
	if (!projectionCalculated)
	{
		if (mode == CameraMode::Perspective)
			projection = glm::perspective(fieldOfView, aspectRatio.x / aspectRatio.y, zNear, zFar);
		else if (mode == CameraMode::Ortho)
			projection = glm::ortho(
				orthoDimensions.Left, orthoDimensions.Right,
				orthoDimensions.Bottom, orthoDimensions.Top);
		
		projectionCalculated = true;
	}
	return projection; // TODO: if projection (or view) unmodified, error (if mode dont match)
}

CameraMode Camera::GetMode() { return mode; }
glm::vec3 Camera::GetPosition() { return position; }
glm::vec3 Camera::GetRotation() { return rotation; }
glm::vec2 Camera::GetAspectRatio() { return aspectRatio; }
Rectangle Camera::GetOrthoDimensions() { return orthoDimensions; }
float Camera::GetFieldOfView() { return fieldOfView; }
float Camera::GetZNear() { return zNear; }
float Camera::GetZFar() { return zFar; }

void Camera::Reset()
{
	viewCalculated = false;
	projectionCalculated = false;
}
void Camera::SetMode(CameraMode value)
{
	mode = value;
	projectionCalculated = false;
}
void Camera::SetPosition(glm::vec3 value)
{
	position = value;
	viewCalculated = false;
}
void Camera::SetRotation(glm::vec3 value)
{
	rotation = value;
	viewCalculated = false;
}
void Camera::SetAspectRatio(glm::vec2 value)
{
	aspectRatio = value;
	projectionCalculated = false;
}
void Camera::SetOrthoDimensions(float left, float right, float top, float bottom)
{
	orthoDimensions = Rectangle(left, right, top, bottom);
	if (mode == CameraMode::Ortho)
		projectionCalculated = false;
}
void Camera::SetOrthoDimensions(Rectangle rectangle)
{
	orthoDimensions = rectangle;
	if (mode == CameraMode::Ortho)
		projectionCalculated = false;
}
void Camera::SetFieldOfView(float value)
{
	fieldOfView = value;
	if (mode == CameraMode::Perspective)
		projectionCalculated = false;
}
void Camera::SetZNear(float value)
{
	zNear = value;
	if (mode == CameraMode::Perspective)
		projectionCalculated = false;
}
void Camera::SetZFar(float value)
{
	zFar = value;
	if (mode == CameraMode::Perspective)
		projectionCalculated = false;
}

Camera::Camera()
{
	position = glm::vec3();
	rotation = glm::vec3();
	aspectRatio = glm::vec2(16, 9);
	orthoDimensions = Rectangle(-128, 128, 128, -128);
	fieldOfView = 90;
	zNear = 0.5;
	zFar = 8192;
	viewCalculated = false;
	projectionCalculated = false;
}
