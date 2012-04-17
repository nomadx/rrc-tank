/*
 * Demo03.hpp
 *
 *  Created on: Apr 16, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMO03_HPP_
#define DEMO03_HPP_

/**
 * Энэ демогоор GPU ашиглаж particle-үүд хөдөлгөж үзэх болно.
 * */

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

#define PARTICLE_TEXTURE_WIDTH 16 // нийт particle-тоо нь энэний квадрат байна.

class Demo03: public AbstractState {
public:
	Demo03();
	~Demo03();

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
	glm::mat4 mvp;


	GLuint textureID;
	GLuint positionTextures[2];

	GLuint positionFramebuffers[2];

	GLuint sphereVAO;
	GLuint verticesSphereVBO;

	GLuint vaoUpdatePoints;
};


#endif /* DEMO03_HPP_ */
