/*
 * Tank.hpp
 *
 *  Created on: Apr 14, 2012
 *      Author: nomadx
 */

#ifndef TANKDEMO_HPP_
#define TANKDEMO_HPP_

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class TankDemo : public AbstractState
{
public:
	TankDemo();
	~TankDemo();

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

	glm::mat4 mvpMat;
	glm::mat4 modelMat;

	GLuint vaoID[2];
	GLuint vboID[3];
};
#endif /** End TankDemo_HPP */
