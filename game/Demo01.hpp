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

	glm::mat4 mvpMat;
	glm::mat4 modelMat; // рэндэрлэж байгаа объектийн хувиргалтын матриц

	GLuint vaoID[1];
	GLuint vboID[2];
	GLuint textureID;
};


#endif /* DEMO01_HPP_ */
