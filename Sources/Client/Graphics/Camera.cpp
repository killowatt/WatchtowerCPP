#include "Camera.h"

using namespace Graphics;

glm::mat4 Camera::GetView()
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
glm::mat4 Camera::GetProjection() // TODO: Make reference for speed?
{
	if (!projectionCalculated)
	{
		projection = glm::perspective(fieldOfView, aspectRatio.x / aspectRatio.y, zNear, zFar);
		projectionCalculated = true;
	}
	return projection;
}

CameraMode Camera::GetMode() { return mode; }
glm::vec3 Camera::GetPosition() { return position; }
glm::vec3 Camera::GetRotation() { return rotation; }
glm::vec2 Camera::GetAspectRatio() { return aspectRatio; }
float Camera::GetFieldOfView() { return fieldOfView; }
float Camera::GetZNear() { return zNear; }
float Camera::GetZFar() { return zFar; }

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