/*
 * Intro.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef INTRO_HPP_
#define INTRO_HPP_

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class Intro : public AbstractState
{
public:
	Intro();
	~Intro();

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

	// рэндэрлэх өгөгдлүүдэд хэрэглэнэ
	glm::mat4 mvpMat;
	glm::mat4 modelMat;

	GLuint vaoID[2];
	GLuint vboID[3];
};

#endif /* INTRO_HPP_ */
