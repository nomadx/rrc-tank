/*
 * Intro.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "Intro.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"
#include "stdio.h"
#include "GL/glew.h"

Intro::Intro() {
	isEntered = true;
	InitializeGL();
}

Intro::~Intro() {
}

void Intro::Pause() {
	isEntered = false;
}
void Intro::Resume() {
	isEntered = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Intro state.");
	glfwSetWindowTitle(str);
}

void Intro::Update() {
	if (isEntered) {
		enteredTime += APP.GetDeltaTime();
		if (enteredTime > 0.5f) {
			isEntered = false;
			enteredTime = 0.0;
		}
	}
	bool spaceButton = APP.GetKey(GLFW_KEY_F1);
	if (spaceButton && !isEntered) {
		Engine *engine = Engine::Instance();
		engine->ChangesState("game");
	}

}
void Intro::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shaderManager["Simple"]->Activate();
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Intro::InitializeGL() {
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	shaderManager.CreateShaderProgram("Simple");
	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/simple-test.vs");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/simple-test.fs");
	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple", "SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple", "SimpleFragment");
	shaderManager.BindAttribute("Simple", 0, "vertexPosition_modelspace");
	shaderManager.LinkProgramObject("Simple");
	shaderManager["Simple"]->Activate();

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(g_vertex_buffer_data),
			g_vertex_buffer_data,
			GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("vertexPosition_modelspace",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("vertexPosition_modelspace");

	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

}
