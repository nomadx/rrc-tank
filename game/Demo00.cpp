/*
 * Demo00.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */


#include "Demo00.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"
#include "stdio.h"
#include "GL/glew.h"

Demo00::Demo00() {
	isEntered = true;
	isFirstTime = true;
	APP.SetCursorVisible(false);
}

Demo00::~Demo00() {
	if (vaoID) {
		glDeleteVertexArrays(1, &vaoID[0]);
	}
	if (vboID) {
		glDeleteBuffers(1, &vboID[0]);
	}
}

void Demo00::Pause() {
	isEntered = false;
}
void Demo00::Resume() {
	isEntered = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Demo00 state.");
	glfwSetWindowTitle(str);

	APP.SetCursorVisible(false);
	if (isFirstTime){
		Initialize();
		isFirstTime = false;
	}
}

void Demo00::Update() {
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

	modelMatrix      = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)); // моделийн матрицыг утгаар цэнэглэх буюу моделийн хэмжээс хоёр дахин том болно гэдгийг тохируулж өглөө
	static float angle = 0.0f;
	angle += APP.GetDeltaTime() * 5.0f;
	modelMatrix      = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));

	viewMatrix       = camera.GetViewMat(); // камераас view матрицийн утгыг авах
	projectionMatrix = camera.GetProjMat(); // камераас projection матрицийн утгыг авах
}
void Demo00::Render() {
	glViewport(0, 0, (int)camera.GetWidth(),(int)camera.GetHeight());
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	shaderManager["Simple"]->Activate(); // shader програмаа хэрэглэж эхлэх
	{
		shaderManager["Simple"]->SetUniformMatrix4fv("modelMatrix"     , 1, GL_FALSE, &modelMatrix     [0][0]); // model матрицийн утгуудыг gpu-рүү илгээх
		shaderManager["Simple"]->SetUniformMatrix4fv("viewMatrix"      , 1, GL_FALSE, &viewMatrix      [0][0]); // view матрицийн утгуудыг gpu-рүү илгээх
		shaderManager["Simple"]->SetUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, &projectionMatrix[0][0]); // projection матрицийн утгуудыг gpu-рүү илгээх
		glBindVertexArray(vaoID[0]); // gpu дээр vaoID[0] байрлалд байгаа өгөгдлийг хэрэглэнэ гэдгийг зааж өглөө
			glDrawArrays(GL_TRIANGLES, 0, 6); // өгөгдлүүдийг зурах
		glBindVertexArray(0); // зурж дууссан бол өгөгдлийн заалтыг default дээр тавих
	}
	shaderManager["Simple"]->Deactivate(); // shader програмаа хэрэглэж болсон бол идэвхигүй болгох
}

void Demo00::Initialize() {
	shaderManager.CreateShaderProgram("Simple"); // shader програм үүсгэх

	shaderManager.AttachShader("SimpleVertex"  , VERTEX); // vertex shader үүсгэх
	shaderManager.AttachShader("SimpleFragment", FRAGMENT); // fragment shader үүсгэх

	shaderManager.LoadShaderSource("SimpleVertex"  , "data/shaders/demo00/demo00-simple.vert.glsl"); // vertex shader програмын кодыг файлаас уншиж авч хадгалах
	shaderManager.LoadShaderSource("SimpleFragment", "data/shaders/demo00/demo00-simple.frag.glsl"); // fragment shader програмын кодыг файлаас уншиж авч хадгалах

	shaderManager.CompileShader("SimpleVertex"); // vertex shader-ээ компайлдах
	shaderManager.CompileShader("SimpleFragment"); // fragment shader-ээ компайлдах

	shaderManager.AttachShaderToProgram("Simple","SimpleVertex"); // компайлдаад үүссэн vertex shader програмаа үндсэн shader програмлуу холбож өгөх
	shaderManager.AttachShaderToProgram("Simple","SimpleFragment"); // компайлдаад үүссэн fragment shader програмаа үндсэн shader програмлуу холбож өгөх

	shaderManager.BindAttribute("Simple",0,"in_Position"); // shader програмын оролтын өгөгдөлд хэрэглэх хувьсагч
	shaderManager.BindAttribute("Simple",1,"in_Color"); // shader програмын оролтын өгөгдөлд хэрэглэх хувьсагч

	shaderManager.LinkProgramObject("Simple"); // үндсэн shader програмаа host програм буюу c++ програмлуугаа холбож өгөх

	shaderManager["Simple"]->Activate(); // shader програм хэрэглэхээр тохируулах


	// эндээс эхлээд gpu-рүү рэндэрлэх гэж байгаа өгөгдлөө upload хийж хуулах үйл ажиллагаа явагдана.

	float* vertices = new float[18];	// дөрвөлжин дүрсний оройнуудын утгыг хадгална
	// дөрвөлжин дүрс үүсгэхийн тулд хоёр ширхэг гурвалжин ашиглана
	vertices[ 0] = -0.5; vertices[ 1] = -0.5; vertices[ 2] = 0.0; // зүүн доод өнцөг // эхний гурвалжин
	vertices[ 3] = -0.5; vertices[ 4] =  0.5; vertices[ 5] = 0.0; // зүүн дээд өнцөг
	vertices[ 6] =  0.5; vertices[ 7] =  0.5; vertices[ 8] = 0.0; // баруун дээд өнцөг
	vertices[ 9] =  0.5; vertices[10] = -0.5; vertices[11] = 0.0; // баруун доод өнцөг // дараагийн гурвалжин
	vertices[12] = -0.5; vertices[13] = -0.5; vertices[14] = 0.0; // зүүн доод өнцөг
	vertices[15] =  0.5; vertices[16] =  0.5; vertices[17] = 0.0; // баруун дээд өнцөг
	// энэ хоёр гурвалжинг нийлүүлээд огторгуйд төсөөлөн бодож үзээрэй.

	float *colors = new float[18];
	colors[ 0] = 1.0; colors[ 1] = 1.0; colors[ 2] = 1.0; // зүүн доод оройны өнгө // эхний гурвалжин
	colors[ 3] = 1.0; colors[ 4] = 0.0; colors[ 5] = 0.0; // зүүн дээд оройны өнгө
	colors[ 6] = 0.0; colors[ 7] = 1.0; colors[ 8] = 0.0; // баруун дээд оройны өнгө
	colors[ 9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // баруун доод оройны өнгө // дараагийн гурвалжин
	colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // зүүн доод оройны өнгө
	colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; // баруун дээд оройны өнгө


	glGenVertexArrays(1, &vaoID[0]); // Vertex Array Object үүсгэх
	glBindVertexArray(vaoID[0]); // үүсгэсэн Vertex Array Object оо хэрэглэхээр тохируулах

	glGenBuffers(2, &vboID[0]); // байршилууд болон өнгөнүүдэд зориулж Vertex Buffer Object-үүд үүсгэх. 2 тоо нь хоёр ширхэг буфер үүсгэж байгааг илтгэнэ
	// цэгэн оройн байршлуудад зориулагдсан буфер үүсгээд өгөгдөл хийх
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // үүсгэсэн Vertex Buffer Object оо хэрэглэхээр тохируулах
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // VBO ийнхөө хэмжээг тохируулөөд өгөгдөл хийх. Ингэснээр gpu дээр үүссэн буфферт цэгүүдийн мэдээлэл upload хийгдэн очих болно
	shaderManager["Simple"]->VertexAttribPointer("in_Position", 3, GL_FLOAT, 0, 0); // vertex attributes заагчийг тохируулах. буферт гурав гурваар нь хандаж авна гэдгийг зааж байна.
	shaderManager["Simple"]->EnableAttribArray("in_Position");
	// оройн өнгөний мэдээлэлд зориулагдсан буфер үүсгээд өгөгдлүүд хийх
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // үүсгэсэн Vertex Buffer Object оо хэрэглэхээр тохируулах
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // VBO ийнхөө хэмжээг тохируулөөд өгөгдөл хийх. Ингэснээр gpu дээр үүссэн буфферт цэгүүдийн мэдээлэл upload хийгдэн очих болно
	shaderManager["Simple"]->VertexAttribPointer("in_Color", 3, GL_FLOAT, 0, 0); // vertex attributes заагчийг тохируулах. буферт гурав гурваар нь хандаж авна гэдгийг зааж байна.
	shaderManager["Simple"]->EnableAttribArray("in_Color");

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	delete [] vertices; // Програмын санах ойд хуваарилаж үүсгэсэн массиваа санах ойгоос устгах. Цаашид ашиглах шаардлагагүй учир нь энэ массив дээрхи өгөгдөл сая GPU-рүү upload хийгдсэн байгаа.
	delete [] colors;   // Програмын санах ойд хуваарилаж үүсгэсэн массиваа санах ойгоос устгах. Цаашид ашиглах шаардлагагүй учир нь энэ массив дээрхи өгөгдөл сая GPU-рүү upload хийгдсэн байгаа.
}



