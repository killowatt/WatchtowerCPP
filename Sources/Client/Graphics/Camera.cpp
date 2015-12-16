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
glm::mat4& Camera::GetProjection()
{
	if (!projectionCalculated)
	{
		if (mode == CameraMode::Perspective)
			projection = glm::perspective(fieldOfView, aspectRatio.x / aspectRatio.y, zNear, zFar);
		else if (mode == CameraMode::Ortho)
		{
			if (orthoDepthEnabled == false)
				projection = glm::ortho(
					orthoDimensions.Left, orthoDimensions.Right,
					orthoDimensions.Bottom, orthoDimensions.Top);
			else
				projection = glm::ortho(
					orthoDimensions.Left, orthoDimensions.Right,
					orthoDimensions.Bottom, orthoDimensions.Top,
					zNear, zFar);
		}
		projectionCalculated = true;
	}
	return projection; // TODO: if projection (or view) unmodified, error (if mode dont match)
}

CameraMode Camera::GetMode() const { return mode; }
glm::vec3 Camera::GetPosition() const { return position; }
glm::vec3 Camera::GetRotation() const { return rotation; }
glm::vec2 Camera::GetAspectRatio() const { return aspectRatio; }
float Camera::GetFieldOfView() const { return fieldOfView; }
float Camera::GetZNear() const { return zNear; }
float Camera::GetZFar() const { return zFar; }
bool Camera::GetOrthoDepthEnabled() const { return orthoDepthEnabled; }
Rectangle Camera::GetOrthoDimensions() const { return orthoDimensions; }

void Camera::Reset()
{
	viewCalculated = false;
	projectionCalculated = false;
}
void Camera::Calculate()
{
	GetProjection();
	GetView();
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
void Camera::SetPositionX(float value)
{
	rotation.x = value;
	viewCalculated = false;
}
void Camera::SetPositionY(float value)
{
	rotation.y = value;
	viewCalculated = false;
}
void Camera::SetPositionZ(float value)
{
	rotation.z = value;
	viewCalculated = false;
}
void Camera::SetRotation(glm::vec3 value)
{
	rotation = value;
	viewCalculated = false;
}
void Camera::SetRotationX(float value)
{
	rotation.x = value;
	viewCalculated = false;
}
void Camera::SetRotationY(float value)
{
	rotation.y = value;
	viewCalculated = false;
}
void Camera::SetRotationZ(float value)
{
	rotation.z = value;
	viewCalculated = false;
}
void Camera::SetAspectRatio(glm::vec2 value)
{
	aspectRatio = value;
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
void Camera::SetOrthoDepthEnabled(bool value)
{
	orthoDepthEnabled = value;
	if (mode == CameraMode::Ortho)
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

Camera::Camera()
{
	mode = CameraMode::Perspective;
	position = glm::vec3();
	rotation = glm::vec3();
	aspectRatio = glm::vec2(16, 9);
	fieldOfView = 90;
	zNear = 0.5;
	zFar = 8192;
	orthoDepthEnabled = true;
	orthoDimensions = Rectangle(-128, 128, 128, -128);
	viewCalculated = false;
	projectionCalculated = false;
}
