/*
 * Demo04.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: sharavsambuu
 */

#include "Demo04.hpp"
#include "../graphics/ObjModel.hpp"
#include <memory>

Demo04::Demo04()
{
	isEntered   = true;
	isFirstTime = true;
	APP.SetCursorVisible(false);
}
Demo04::~Demo04()
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


void Demo04::Pause() {
	isEntered = false;
}
void Demo04::Resume() {
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

void Demo04::Update() {
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
		engine->ChangesState("demo01");
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

	modelMatrix      = glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)), 90.0f, glm::vec3(0,0,1));
	viewMatrix       = camera.GetViewMat();
	projectionMatrix = camera.GetProjMat();

	normalMatrix = glm::inverse(glm::transpose(glm::mat3(viewMatrix*modelMatrix)));
}
void Demo04::Render() {
	glViewport(0, 0, (int)camera.GetWidth(),(int)camera.GetHeight());
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager["Simple"]->Activate();
	{
		shaderManager["Simple"]->SetUniformMatrix4fv("u_modelMatrix"     , 1, GL_FALSE, &modelMatrix     [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("u_viewMatrix"      , 1, GL_FALSE, &viewMatrix      [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("u_projectionMatrix", 1, GL_FALSE, &projectionMatrix[0][0]);
		shaderManager["Simple"]->SetUniformMatrix3fv("u_normalMatrix"    , 1, GL_FALSE, &normalMatrix    [0][0]);
		shaderManager["Simple"]->SetUniformMatrix4fv("u_lightPosition"   , 1, GL_FALSE, &modelMatrix     [0][0]);

		shaderManager["Simple"]->SetUniform4fv("u_lightPosition" , 1, lightPosition);

		glBindVertexArray(vaoID[0]);
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[0]);
			glDrawElements(GL_TRIANGLES, triangleCount * 3, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
	}
	shaderManager["Simple"]->Deactivate();
}

void Demo04::Initialize() {
	shaderManager.CreateShaderProgram("Simple");

	shaderManager.AttachShader("SimpleVertex"  , VERTEX);
	shaderManager.AttachShader("SimpleFragment", FRAGMENT);
	shaderManager.AttachShader("SimpleGeometry", GEOMETRY);

	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/demo04/dublicate.vert.glsl");
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/demo04/dublicate.frag.glsl");
	shaderManager.LoadShaderSource("SimpleGeometry", "data/shaders/demo04/dublicate.geom.glsl");

	shaderManager.CompileShader("SimpleVertex");
	shaderManager.CompileShader("SimpleFragment");
	shaderManager.CompileShader("SimpleGeometry");

	shaderManager.AttachShaderToProgram("Simple", "SimpleVertex");
	shaderManager.AttachShaderToProgram("Simple", "SimpleFragment");
	shaderManager.AttachShaderToProgram("Simple", "SimpleGeometry");

	shaderManager.BindAttribute("Simple", 0, "a_vertex");
	shaderManager.BindAttribute("Simple", 1, "a_normal");

	shaderManager.LinkProgramObject("Simple");

	shaderManager["Simple"]->Activate();


	lightPosition[0] = 0.0f;
	lightPosition[1] = 0.5f;
	lightPosition[2] = 2.0f;
	lightPosition[3] = 1.0f;

	std::auto_ptr<ObjModel> model(new ObjModel);
	model->Load("data/model/obj/bunny.obj");
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
	shaderManager["Simple"]->VertexAttribPointer("a_vertex", 3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
	shaderManager["Simple"]->VertexAttribPointer("a_normal", 3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderManager["Simple"]->EnableAttribArray("a_vertex");
	shaderManager["Simple"]->EnableAttribArray("a_normal");
	glBindVertexArray(0);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}



