/*
 * Demo01.cpp
 *
 *  Created on: Apr 14, 2012
 *      Author: sharavsambuu
 */

#include "Demo01.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"
#include "stdio.h"
#include "GL/glew.h"

Demo01::Demo01() {
	isEntered = true;
	InitializeGL();
	APP.SetCursorVisible(false);
}

Demo01::~Demo01() {
}

void Demo01::Pause() {
	isEntered = false;
}
void Demo01::Resume() {
	isEntered = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Intro state.");
	glfwSetWindowTitle(str);

	APP.SetCursorVisible(false);
}

void Demo01::Update() {
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

	bool shouldMoveForward  = APP.GetKey('W');
	bool shouldMoveBackward = APP.GetKey('S');
	bool shouldMoveLeft     = APP.GetKey('A');
	bool shouldMoveRight    = APP.GetKey('D');
	camera.MoveForward (shouldMoveForward);
	camera.MoveBackward(shouldMoveBackward);
	camera.MoveLeft    (shouldMoveLeft);
	camera.MoveRight   (shouldMoveRight);
	camera.UpdateFOV(APP.GetMouseWheel());

	float angleX = (float)APP.GetDeltaX();
	float angleY = (float)APP.GetDeltaY();
	camera.UpdateAngles(angleX, angleY);

	camera.Update();

	mvpMat =  modelMat * camera.GetProjMat() * camera.GetViewMat();
}
void Demo01::Render() {
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager["Simple"]->Activate();
	shaderManager["Simple"]->SetUniformMatrix4fv("uMVP", 1, GL_FALSE, &mvpMat[0][0]);

	glBindVertexArray(vaoID[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Demo01::InitializeGL() {
	shaderManager.CreateShaderProgram("Simple");

	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/demo01/simple-test.vs");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/demo01/simple-test.fs");

	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple","SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple","SimpleFragment");

	shaderManager.BindAttribute("Simple",0,"inPosition");
	shaderManager.BindAttribute("Simple",1,"inColour");

	shaderManager.LinkProgramObject("Simple");
	shaderManager["Simple"]->Activate();

	modelMat = glm::mat4(1);

	// эхний объект
	float* vert = new float[12];	// vertex array
	float* col  = new float[12];	// color array
	vert[0] =-0.8; vert[ 1] = 0.5; vert[ 2] =-1.0;
	vert[3] =-0.8; vert[ 4] =-0.5; vert[ 5] =-1.0;
	vert[6] = 0.2; vert[ 7] =-0.5; vert[ 8]= -1.0;
	vert[9] = 0.2; vert[10] = 0.5; vert[11]= -1.0;
	col[0] = 1.0; col[ 1] = 0.0; col[ 2] = 0.0;
	col[3] = 0.0; col[ 4] = 1.0; col[ 5] = 0.0;
	col[6] = 0.0; col[ 7] = 0.0; col[ 8] = 1.0;
	col[9] = 1.0; col[10] = 0.0; col[11] = 1.0;

	glGenVertexArrays(1, &vaoID[0]); // хоёр ширхэг VAO үүсгэх

	// эхний VAO
	glBindVertexArray(vaoID[0]);
	glGenBuffers(2, vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), vert, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inPosition",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inPosition");
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), col, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inColour",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inColour");

	delete [] vert;
	delete [] col;

}



