/*
 * Demo02.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */

#include "Demo02.hpp"
#include "../graphics/ObjModel.hpp"
#include <memory>

Demo02::Demo02()
{
	isEntered   = true;
	isFirstTime = true;
	APP.SetCursorVisible(false);
}
Demo02::~Demo02()
{
	if (vaoID) {
		glDeleteVertexArrays(1, &vaoID[0]);
	}
	if (vboID) {
		glDeleteBuffers(3, &vboID[0]);
	}
	if (textureID) {
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
}


void Demo02::Pause() {
	isEntered = false;
}
void Demo02::Resume() {
	isEntered = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Demo01 state.");
	glfwSetWindowTitle(str);

	APP.SetCursorVisible(false);

	if(isFirstTime)
	{
		Initialize();
		isFirstTime = false;
	}
}

void Demo02::Update() {
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
		engine->ChangesState("intro");
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
void Demo02::Render() {
	glViewport(0, 0, (int)camera.GetWidth(),(int)camera.GetHeight());
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	shaderManager["Simple"]->Activate();
	{
		shaderManager["Simple"]->SetUniformMatrix4fv("modelMatrix"     , 1, GL_FALSE, &modelMatrix     [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("viewMatrix"      , 1, GL_FALSE, &viewMatrix      [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, &projectionMatrix[0][0]);

		glBindVertexArray(vaoID[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[0]);
			glDrawElements(GL_TRIANGLES, triangleCount * 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	shaderManager["Simple"]->Deactivate();
}

void Demo02::Initialize() {
	shaderManager.CreateShaderProgram("Simple");

	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/demo02/texture.vert.glsl");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/demo02/grey.frag.glsl");

	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple", "SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple", "SimpleFragment");

	shaderManager.BindAttribute("Simple", 0, "inPosition");
	shaderManager.BindAttribute("Simple", 1, "inNormal");

	shaderManager.LinkProgramObject("Simple");
	shaderManager["Simple"]->Activate();

	//----------------------------
	std::auto_ptr<ObjModel> model(new ObjModel);
	model->Load("data/model/obj/dragon.obj");
			triangleCount = model->faces.size();
	GLsizei vertexCount   = model->vertices.size();

	glGenBuffers(3, &vboID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[0]); // elements
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*triangleCount, &*model->faces.begin(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)*3*vertexCount, &*model->vertices.begin(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // normals
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)*3*vertexCount, &*model->normals.begin(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoID[0]);
	glBindVertexArray(vaoID[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	shaderManager["Simple"]->VertexAttribPointer("inPosition", 3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
	shaderManager["Simple"]->VertexAttribPointer("inNormal", 3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderManager["Simple"]->EnableAttribArray("inPosition");
	shaderManager["Simple"]->EnableAttribArray("inNormal");
	glBindVertexArray(0);


}



