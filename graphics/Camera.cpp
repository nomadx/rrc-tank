/*
 * Camera.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: sharavsambuu
 */

#include "Camera.hpp"
#include "../system/GLFW_App.hpp"
#include "../util/Util.hpp"
#include "math.h"

Camera::Camera()
{
	pos           = glm::vec3(0, 0, -3);
	horizontAngle = 0.0f;
	verticalAngle = 0.0f;
	width         = 800.0f;
	height        = 600.0f;
	moveSpeed     = 1.0f;
	sensitivity   = 0.001f;
	fov           = 60.0f;
	zNear         = 0.01;
	zFar          = 1000.0f;
}
Camera::~Camera()
{
}

void Camera::Update()
{
	float dt = APP.GetDeltaTime();

	dir = glm::vec3(
		cos(verticalAngle) * sin(horizontAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontAngle)
	);
	glm::vec3 right = glm::vec3(
		sin(horizontAngle - M_PI/2.0f),
		0,
		cos(horizontAngle - M_PI/2.0f)
	);
	up = glm::cross(right, dir);

	if (moveForward)
		pos += dir * moveSpeed * dt;
	if (moveBackward)
		pos -= dir * moveSpeed * dt;
	if (moveRight)
		pos += right * moveSpeed * dt;
	if (moveLeft)
		pos -= right * moveSpeed * dt;

	if (!height>0)
		height = 1;
	projMat = glm::perspective(fov, width/height, zNear, zFar);
	viewMat = glm::lookAt(pos, pos + dir, up);

}

glm::mat4 Camera::GetViewMat()
{
	return viewMat;
}
glm::mat4 Camera::GetProjMat()
{
	return projMat;
}
glm::mat4 Camera::GetVPMat()
{
	return projMat * viewMat;
}

glm::vec3 Camera::GetPos()
{
	return pos;
}
glm::vec3 Camera::GetDir()
{
	return dir;
}
glm::vec3 Camera::GetUp()
{
	return up;
}

float Camera::GetWidth()
{
	return width;
}

float Camera::GetHeight()
{
	return height;
}

void Camera::UpdateAngles(float hori, float vert)
{
	horizontAngle -= hori * sensitivity;
	verticalAngle -= vert * sensitivity;
}
void Camera::UpdateHorizontalAngle(float hori)
{
	horizontAngle -= hori;
}
void Camera::UpdateVerticalAngle(float vert)
{
	verticalAngle -= vert;
}
void Camera::SetDim(float height, float width)
{
	this->height = height;
	this->width  = width;
}
void Camera::UpdateFOV(float fov)
{
	this->fov += fov/100;
}

void Camera::MoveForward(bool b)
{
	moveForward = b;
}
void Camera::MoveBackward(bool b)
{
	moveBackward = b;
}
void Camera::MoveLeft(bool b)
{
	moveLeft = b;
}
void Camera::MoveRight(bool b)
{
	moveRight = b;
}


