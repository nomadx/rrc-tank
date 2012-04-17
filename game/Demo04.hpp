/*
 * Demo04.hpp
 *
 *  Created on: Apr 17, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMO04_HPP_
#define DEMO04_HPP_

/**
 * Энэ демогоор Geometry Shader програмыг ашиглаж үзэх болно
 * */

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class Demo04: public AbstractState {
public:
	Demo04();
	~Demo04();

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
	glm::mat3 normalMatrix;

	GLuint vaoID[1]; // Vertex Array Object
	GLuint vboID[3]; // Vertex Buffer Object {element, positions, normals}
	GLuint textureID; // texture

	GLsizei triangleCount;


    GLfloat lightPosition[4];
};


#endif /* DEMO04_HPP_ */
