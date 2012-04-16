/*
 * Demo02.hpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMO02_HPP_
#define DEMO02_HPP_

/**
 * Энэ демогоор phong загвараар рэндэрлэлт хийх болно.
 * */

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class Demo02: public AbstractState {
public:
	Demo02();
	~Demo02();

	void Pause();
	void Resume();

	void Update();
	void Render();

	void Initialize();

protected:
private:
	bool isEntered;
	bool isFirstTime;
	float enteredTime;

	Camera camera;
	ShaderManager shaderManager;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	GLuint vaoID[2]; // Vertex Array Object {vertex, normal}
	GLuint vboID[3]; // Vertex Buffer Object {element, positions, normals}
	GLuint textureID; // texture

	GLsizei triangleCount;
};

#endif /* DEMO02_HPP_ */
