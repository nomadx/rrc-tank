/*
 * Camera.hpp
 *
 *  Created on: Apr 12, 2012
 *      Author: sharav
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	glm::mat4 GetViewMat();
	glm::mat4 GetProjMat();
	glm::mat4 GetVPMat();

	glm::vec3 GetPos();
	glm::vec3 GetDir();
	glm::vec3 GetUp();

	float GetWidth();
	float GetHeight();

	void UpdateAngles(float hori, float vert);
	void UpdateHorizontalAngle(float hori);
	void UpdateVerticalAngle  (float vert);
	void SetDim(float height, float width);
	void UpdateFOV(float fov);

	void MoveForward (bool b);
	void MoveBackward(bool b);
	void MoveLeft    (bool b);
	void MoveRight   (bool b);
protected:
private:
	glm::mat4 viewMat;
	glm::mat4 projMat;

	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	float horizontAngle;
	float verticalAngle;

	float moveSpeed;
	float sensitivity;

	float fov;
	float zNear;
	float zFar;

	float width;
	float height;

	bool moveForward;
	bool moveBackward;
	bool moveLeft;
	bool moveRight;
};


#endif /* CAMERA_HPP_ */
