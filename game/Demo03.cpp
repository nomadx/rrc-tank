/*
 * Demo03.cpp
 *
 *  Created on: Apr 16, 2012
 *      Author: sharavsambuu
 */

#include "Demo03.hpp"

Demo03::Demo03()
{
	isEntered   = true;
	isFirstTime = true;
	APP.SetCursorVisible(false);
}

Demo03::~Demo03()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (verticesSphereVBO)
    {
        glDeleteBuffers(1, &verticesSphereVBO);
        verticesSphereVBO = 0;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (textureID)
    {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (positionFramebuffers[0])
    {
        glDeleteFramebuffers(1, &positionFramebuffers[0]);
        positionFramebuffers[0] = 0;
    }
    if (positionFramebuffers[1])
    {
        glDeleteFramebuffers(1, &positionFramebuffers[1]);
        positionFramebuffers[1] = 0;
    }
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (positionTextures[0])
    {
        glDeleteTextures(1, &positionTextures[0]);
        positionTextures[0] = 0;
    }
    if (positionTextures[1])
    {
        glDeleteTextures(1, &positionTextures[1]);
        positionTextures[1] = 0;
    }
    glBindVertexArray(0);
    if (sphereVAO)
    {
        glDeleteVertexArrays(1, &sphereVAO);
        sphereVAO = 0;
    }
    if (vaoUpdatePoints)
    {
        glDeleteVertexArrays(1, &vaoUpdatePoints);
        vaoUpdatePoints = 0;
    }
    glUseProgram(0);
}

void Demo03::Pause() {
	isEntered = false;
}

void Demo03::Resume() {
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

void Demo03::Update() {
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

	modelMatrix      = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	viewMatrix       = camera.GetViewMat();
	projectionMatrix = camera.GetProjMat();

	mvp = projectionMatrix * viewMatrix * modelMatrix;
}
void Demo03::Render() {

	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static GLint flip = 0; // buffer-үүдийн хооронд шилжихэд зориулагдсан buffer

	static GLfloat time = 0;
	time += APP.GetDeltaTime()*10;

	shaderManager["PointUpdater"]->Activate(); // particle-ийн тоон өгөгдлүүдийг шинэчлэх
	shaderManager["PointUpdater"]->SetUniform1f("u_time", APP.GetDeltaTime());
	glBindFramebuffer(GL_FRAMEBUFFER, positionFramebuffers[(flip + 1) % 2]); // бичих Buffer-ээ bind хийх
	glViewport(0, 0, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH); // текстурийн хэмжээгээр viewport-оо тохируулах
	glBindTexture(GL_TEXTURE_2D, positionTextures[flip]); // энэ текстур одоогийн particle өгөгдлүүдийг агуулна
	glBindVertexArray(vaoUpdatePoints);
	glDrawArrays(GL_POINTS, 0, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH); // бүх particle-үүдийг зурах, өгөгдөл нь shader програм дотор шинэчлэгдэнэ

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // window buffer-лүү буцааж тохируулах
	glViewport(0, 0, (int)camera.GetWidth(),(int)camera.GetHeight()); // viewport-оо хэвэнд нь аваачих

	glClear(GL_COLOR_BUFFER_BIT); // particle-уудыг дэлгэцэнд зурж эхлэх
	shaderManager["Particle"]->Activate();
	shaderManager["Particle"]->SetUniformMatrix4fv("u_modelViewProjectionMatrix", 1, GL_FALSE, &mvp[0][0]);
	glBindVertexArray(sphereVAO);
	glBindTexture(GL_TEXTURE_2D, positionTextures[flip]); // particle өгөгдлүүдийг хэрэглэх. Дараагийн фрэймд шинэчлэгдэнэ
	glEnable(GL_BLEND); // цэгүүдийг нэвтрэлттэй байдлаар зурах
	glDrawArrays(GL_POINTS, 0, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH);
	glDisable(GL_BLEND);

	flip = (flip + 1) % 2; // дараагийн буферлүү шилжүүлэх

}

void Demo03::Initialize() {
    // particle өгөгдлүүдийг агуулах бөгөөд texel-д хандахад зориулагдсан цэгүүд
    GLfloat points[PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 2];
    // эхний particle-үүдийг агуулах массив
    GLfloat particle[PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 4];
    GLuint x, y;
	for (y = 0; y < PARTICLE_TEXTURE_WIDTH; y++) {
	   for (x = 0; x < PARTICLE_TEXTURE_WIDTH; x++) {
		   points[x * 2 + 0 + y * PARTICLE_TEXTURE_WIDTH * 2] = (GLfloat) x / (GLfloat) PARTICLE_TEXTURE_WIDTH;
		   points[x * 2 + 1 + y * PARTICLE_TEXTURE_WIDTH * 2] = (GLfloat) y / (GLfloat) PARTICLE_TEXTURE_WIDTH;
	   }
	}
	for (y = 0; y < PARTICLE_TEXTURE_WIDTH; y++) {
	   for (x = 0; x < PARTICLE_TEXTURE_WIDTH; x++) {
		   particle[x * 4 + 0 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
		   particle[x * 4 + 1 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
		   particle[x * 4 + 2 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
		   particle[x * 4 + 3 + y * PARTICLE_TEXTURE_WIDTH * 4] = -1.0f; // w < 0.0 гэдэг нь particle үхсэн гэсэн үг. тэгэхээр дараагийн фрэймд дахин шинэчлэгдэнэ.
	   }
	}


	// particle shader
	shaderManager.CreateShaderProgram("Particle");
	shaderManager.AttachShader("ParticleVertex"  , VERTEX);
	shaderManager.AttachShader("ParticleFragment", FRAGMENT);
	shaderManager.LoadShaderSource("ParticleVertex"  , "data/shaders/demo03/particle.vert.glsl");
	shaderManager.LoadShaderSource("ParticleFragment", "data/shaders/demo03/particle.frag.glsl");
	shaderManager.CompileShader("ParticleVertex");
	shaderManager.CompileShader("ParticleFragment");
	shaderManager.AttachShaderToProgram("Particle", "ParticleVertex");
	shaderManager.AttachShaderToProgram("Particle", "ParticleFragment");
	shaderManager.BindAttribute("Particle", 0, "a_vertex");
	shaderManager.LinkProgramObject("Particle");
	// point updater shader
	shaderManager.CreateShaderProgram("PointUpdater");
	shaderManager.AttachShader("PointUpdaterVertex"  , VERTEX);
	shaderManager.AttachShader("PointUpdaterFragment", FRAGMENT);
	shaderManager.LoadShaderSource("PointUpdaterVertex"  , "data/shaders/demo03/update_points.vert.glsl");
	shaderManager.LoadShaderSource("PointUpdaterFragment", "data/shaders/demo03/update_points.frag.glsl");
	shaderManager.CompileShader("PointUpdaterVertex");
	shaderManager.CompileShader("PointUpdaterFragment");
	shaderManager.AttachShaderToProgram("PointUpdater", "PointUpdaterVertex");
	shaderManager.AttachShaderToProgram("PointUpdater", "PointUpdaterFragment");
	shaderManager.BindAttribute("PointUpdater", 0, "a_vertex");
	shaderManager.LinkProgramObject("PointUpdater");


	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glfwLoadTexture2D("data/images/textures/particle.tga", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(2, positionTextures);

    glBindTexture(GL_TEXTURE_2D, positionTextures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH, 0, GL_RGBA, GL_FLOAT, particle); // float төрөлтэй тоонууд агуулсан текстур үүсгэх
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Чухал : ямар ч дөхөлтгүй.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, positionTextures[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH, 0, GL_RGBA, GL_FLOAT, particle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);


    glGenFramebuffers(2, positionFramebuffers); // хоёр ширхэг framebuffer үүсгэх
	glBindFramebuffer(GL_FRAMEBUFFER, positionFramebuffers[0]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTextures[0], 0); // текстур зураг зааж өгөх
	glBindFramebuffer(GL_FRAMEBUFFER, positionFramebuffers[1]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTextures[1], 0); // текстур зураг зааж өгөх
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glGenBuffers(1, &verticesSphereVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesSphereVBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 2 * sizeof(GLfloat), (GLfloat*) points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	shaderManager["Particle"]->Activate();
    glActiveTexture(GL_TEXTURE0);
    shaderManager["Particle"]->SetUniform1i("u_texture", 0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    shaderManager["Particle"]->SetUniform1i("u_positionTexture", 0);
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesSphereVBO);
    shaderManager["Particle"]->VertexAttribPointer("a_vertex", 2, GL_FLOAT, GL_FALSE, 0, 0);
    shaderManager["Particle"]->EnableAttribArray("a_vertex");
    shaderManager["Particle"]->Deactivate();


    shaderManager["PointUpdater"]->Activate();
    shaderManager["PointUpdater"]->SetUniform1i("u_positionTexture", 1); // texture unit 1 идэвхитэй байгаа.
    shaderManager["PointUpdater"]->SetUniform1f("u_positionTextureWidth", (GLfloat) PARTICLE_TEXTURE_WIDTH);

    glGenVertexArrays(1, &vaoUpdatePoints); // програм бүрт VAO ашиглах болно
	glBindVertexArray(vaoUpdatePoints);
	glBindBuffer(GL_ARRAY_BUFFER, verticesSphereVBO);
	shaderManager["PointUpdater"]->VertexAttribPointer("a_vertex", 2, GL_FLOAT, GL_FALSE, 0, 0);
	shaderManager["PointUpdater"]->EnableAttribArray("a_vertex");


    glEnable(GL_PROGRAM_POINT_SIZE); // gl_PointSize-ийг shader програмд хэрэглэнэ
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // particle-үүдийг нэвтрэлттэй харуулах үүрэгтэй
}
