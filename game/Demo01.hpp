/*
 * Demo01.hpp
 *
 *  Created on: Apr 14, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMO01_HPP_
#define DEMO01_HPP_

/**
 * Энэ демогоор пикселийн өнгийг шүүж сааралтуулж үзэх болно
 * */

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class Demo01 : public AbstractState
{
public:
	Demo01();
	~Demo01();

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

	GLuint vaoID[1];  // Vertex Array Object
	GLuint vboID[2];  // Vertex Buffer Object {positions, texCoords}
	GLuint textureID; // texture
};


#endif /* DEMO01_HPP_ */
