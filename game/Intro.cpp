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
	bool changeButton = APP.GetKey(GLFW_KEY_F1);
	if (changeButton && !isEntered) {
		Engine *engine = Engine::Instance();
		engine->ChangesState("game");
	}

}
void Intro::Render() {
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager["Simple"]->Activate();

	glBindVertexArray(vaoID[0]);		// эхний VAO-г сонгох
	glDrawArrays(GL_TRIANGLES, 0, 3);	// эхний объектийг зурах

	glBindVertexArray(vaoID[1]);		// хоёр дахь VAO
	shaderManager["Simple"]->VertexAttrib3f("inColour",1.0,0.0,0.0);
	//glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute
	glDrawArrays(GL_TRIANGLES, 0, 3);	// хоёр дахь объектийг зурах
}

void Intro::InitializeGL() {
	shaderManager.CreateShaderProgram("Simple");

	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/simple-test.vs");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/simple-test.fs");

	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple","SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple","SimpleFragment");

	shaderManager.BindAttribute("Simple",0,"inPosition");
	shaderManager.BindAttribute("Simple",1,"inColour");

	shaderManager.LinkProgramObject("Simple");
	shaderManager["Simple"]->Activate();


	// эхний объект
	float* vert = new float[9];	// vertex array
	float* col  = new float[9];	// color array
	vert[0] =-0.3; vert[1] = 0.5; vert[2] =-1.0;
	vert[3] =-0.8; vert[4] =-0.5; vert[5] =-1.0;
	vert[6] = 0.2; vert[7] =-0.5; vert[8]= -1.0;
	col[0] = 1.0; col[1] = 0.0; col[2] = 0.0;
	col[3] = 0.0; col[4] = 1.0; col[5] = 0.0;
	col[6] = 0.0; col[7] = 0.0; col[8] = 1.0;

	// хоёр дахь объект
	float* vert2 = new float[9];	// vertex array
	vert2[0] =-0.2; vert2[1] = 0.5; vert2[2] =-1.0;
	vert2[3] = 0.3; vert2[4] =-0.5; vert2[5] =-1.0;
	vert2[6] = 0.8; vert2[7] = 0.5; vert2[8]= -1.0;

	glGenVertexArrays(2, &vaoID[0]); // хоёр ширхэг VAO үүсгэх

	// эхний VAO
	glBindVertexArray(vaoID[0]);
	glGenBuffers(2, vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vert, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inPosition",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inPosition");
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), col, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inColour",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inColour");

	// хоёр дахь VAO
	glBindVertexArray(vaoID[1]);
	glGenBuffers(1, &vboID[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vert2, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	delete [] vert;
	delete [] vert2;
	delete [] col;

}
