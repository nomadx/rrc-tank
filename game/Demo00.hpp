/*
 * Demo00.hpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMO00_HPP_
#define DEMO00_HPP_

/**
 * Энэ демогоор VBO болон VAO нарыг хэрхэн хэрэглэх талаар үзэх болно.
 * */


#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class Demo00 : public AbstractState
{
public:
	Demo00();
	~Demo00();

	void Pause();
	void Resume();

	void Update();
	void Render();

	void Initialize();

protected:
private:
	bool isEntered;
	float enteredTime;

	Camera camera;
	ShaderManager shaderManager;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	GLuint vaoID[1]; // Vertex Array Object
	GLuint vboID[1]; // Vertex Buffer Object
};



#endif /* DEMO00_HPP_ */
