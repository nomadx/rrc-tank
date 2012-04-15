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
	Initialize();
	APP.SetCursorVisible(false);
}

Demo01::~Demo01() {
	glDeleteVertexArrays(1, &vaoID[0]);
	glDeleteBuffers(1, &vboID[0]);
	glDeleteTextures(1, &textureID);
}

void Demo01::Pause() {
	isEntered = false;
}
void Demo01::Resume() {
	isEntered = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Demo01 state.");
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

	modelMatrix      = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	viewMatrix       = camera.GetViewMat();
	projectionMatrix = camera.GetProjMat();
}
void Demo01::Render() {
	glViewport(0, 0, (int)camera.GetWidth(),(int)camera.GetHeight());
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	shaderManager["Simple"]->Activate();
	{
		shaderManager["Simple"]->SetUniformMatrix4fv("modelMatrix"     , 1, GL_FALSE, &modelMatrix     [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("viewMatrix"      , 1, GL_FALSE, &viewMatrix      [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, &projectionMatrix[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		shaderManager["Simple"]->SetUniform1i("uTexture", 0);

		glBindVertexArray(vaoID[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	shaderManager["Simple"]->Deactivate(); // shader програмаа хэрэглэж болсон бол идэвхигүй болгох
}

void Demo01::Initialize() {
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

	// эндээс эхлээд gpu-рүү рэндэрлэх гэж байгаа өгөгдлөө upload хийж хуулах үйл ажиллагаа явагдана.

	float* vertices = new float[18];
	vertices[ 0] = -0.5; vertices[ 1] = -0.5; vertices[ 2] = 0.0; // зүүн доод өнцөг // эхний гурвалжин
	vertices[ 3] = -0.5; vertices[ 4] =  0.5; vertices[ 5] = 0.0; // зүүн дээд өнцөг
	vertices[ 6] =  0.5; vertices[ 7] =  0.5; vertices[ 8] = 0.0; // баруун дээд өнцөг
	vertices[ 9] =  0.5; vertices[10] = -0.5; vertices[11] = 0.0; // баруун доод өнцөг // дараагийн гурвалжин
	vertices[12] = -0.5; vertices[13] = -0.5; vertices[14] = 0.0; // зүүн доод өнцөг
	vertices[15] =  0.5; vertices[16] =  0.5; vertices[17] = 0.0; // баруун дээд өнцөг

	float *coords = new float[12];
	coords[ 0] = 0.0; coords[ 1] = 0.0; // зүүн доод оройны өнгө // эхний гурвалжин
	coords[ 2] = 0.0; coords[ 3] = 1.0; // зүүн дээд оройны өнгө
	coords[ 4] = 1.0; coords[ 5] = 1.0; // баруун дээд оройны өнгө
	coords[ 6] = 1.0; coords[ 7] = 0.0; // баруун доод оройны өнгө // дараагийн гурвалжин
	coords[ 8] = 0.0; coords[ 9] = 0.0; // зүүн доод оройны өнгө
	coords[10] = 1.0; coords[11] = 1.0; // баруун дээд оройны өнгө


	glGenVertexArrays(1, &vaoID[0]);
	glBindVertexArray(vaoID[0]);

	glGenBuffers(2, &vboID[0]);
	// цэгэн оройн байршлуудад зориулагдсан буфер үүсгээд өгөгдөл хийх
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inPosition", 3, GL_FLOAT, 0, 0);
	shaderManager["Simple"]->EnableAttribArray("inPosition");
	// текстур буулгалтын координатуудад зориулагдсан буфер үүсгээд өгөгдлүүд хийх
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), coords, GL_STATIC_DRAW);
	shaderManager["Simple"]->VertexAttribPointer("inTexCoord", 2, GL_FLOAT, 0, 0);
	shaderManager["Simple"]->EnableAttribArray("inTexCoord");

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	delete [] vertices;
	delete [] coords;

	// текстур зураг уншиж авах хэсэг
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



