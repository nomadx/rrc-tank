/*
 * DemoPixel.hpp
 *
 *  Created on: Apr 14, 2012
 *      Author: sharavsambuu
 */

#ifndef DEMOPIXEL_HPP_
#define DEMOPIXEL_HPP_

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../graphics/ShaderManager.hpp"
#include "../graphics/Camera.hpp"

class DemoPixel : public AbstractState
{
public:
	DemoPixel();
	~DemoPixel();

	void Pause();
	void Resume();

	void Update();
	void Render();

	void InitializeGL();

protected:
private:
	bool isEntered;
	float enteredTime;

	Camera camera;
	ShaderManager shaderManager;

	glm::mat4 mvpMat;
	glm::mat4 modelMat;

	GLuint vaoID[2];
	GLuint vboID[3];
};

#endif /* DEMOPIXEL_HPP_ */
