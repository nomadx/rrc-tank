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

struct LightProperties
{
    GLfloat direction[3];
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
};
struct MaterialProperties
{
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
    GLfloat specularExponent;
};


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
	glm::mat3 normalMatrix;

	GLuint vaoID[2]; // Vertex Array Object {vertex, normal}
	GLuint vboID[3]; // Vertex Buffer Object {element, positions, normals}
	GLuint textureID; // texture

	GLsizei triangleCount;

    struct LightProperties    light;
    struct MaterialProperties material;
};

#endif /* DEMO02_HPP_ */
