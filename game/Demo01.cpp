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
	glBindTexture(GL_TEXTURE_2D, textureID);
	shaderManager["Simple"]->SetUniform1i("uTexture", 0);

	glBindVertexArray(vaoID[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	shaderManager["Simple"]->Deactivate();
}

void Demo01::InitializeGL() {
	shaderManager.CreateShaderProgram("Simple");

	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/demo01/texture.vert.glsl");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/demo01/grey.frag.glsl");

	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple", "SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple", "SimpleFragment");

	shaderManager.BindAttribute("Simple", 0, "inPosition");
	shaderManager.BindAttribute("Simple", 1, "inTexCoord");

	shaderManager.LinkProgramObject("Simple");
	shaderManager["Simple"]->Activate();


	modelMat = glm::mat4(1);
	//modelMat = glm::translate(modelMat, glm::vec3(0,-1.5,0));

	float* vert = new float[12];
	/*{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 1.0f,
		 0.0f,  1.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f,-1.0f};*/
	vert[0] =  1.0f; vert[ 1] = 0.0f; vert[ 2] =-1.0f;
	vert[3] =  1.0f; vert[ 4] = 0.0f; vert[ 5] = 1.0f;
	vert[6] = -1.0f; vert[ 7] = 0.0f; vert[ 8]=  1.0f;
	vert[9] = -1.0f; vert[10] = 0.0f; vert[11]= -1.0f;

	float* texCoords  = new float[8];
	texCoords[0] = 0.0f; texCoords[1] = 0.0f;
	texCoords[2] = 1.0f; texCoords[3] = 0.0f;
	texCoords[4] = 1.0f; texCoords[5] = 1.0f;
	texCoords[6] = 0.0f; texCoords[7] = 1.0f;
	//for (int i=0; i<8; i++)
		//texCoords[i] *= 150;

	glGenVertexArrays(1, &vaoID[0]);
	glBindVertexArray(vaoID[0]);
	glGenBuffers(2, vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), vert, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inPosition",3,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inPosition");
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inTexCoord",2,GL_FLOAT,0,0);
	shaderManager["Simple"]->EnableAttribArray("inTexCoord");
	delete [] vert;
	delete [] texCoords;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glfwLoadTexture2D("data/images/textures/sharavaa.tga", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

}



