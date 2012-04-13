/*
 * GLFW_App.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#include "GLFW_App.hpp"
#include "stdlib.h"
#include <stdio.h>

#define GLFW_OPENGL_VERSION_MAJOR 4
#define GLFW_OPENGL_VERSION_MINOR 4
#define GLFW_OPENGL_PROFILE 4
#define GLFW_OPENGL_CORE_PROFILE 4

GLFWApp::GLFWApp()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	wndWidth  = 800; midWidth  = wndWidth/2;
	wndHeight = 600; midHeight = wndHeight/2;
	int redBits   = 8, greenBits = 8,  blueBits    = 8;
	int alphaBits = 8, depthBits = 24, stencilBits = 8;

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwOpenWindow(wndWidth,wndHeight,redBits,greenBits,blueBits,alphaBits,depthBits,stencilBits,GLFW_WINDOW))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	if (GLEW_VERSION_2_1)
	{
		fprintf(stdout, "OpenGL 2.1 is supported\n");
	}
	if (GLEW_VERSION_3_3)
	{
		fprintf(stdout, "OpenGL 3.3 is supported\n");
	}
	if (GLEW_VERSION_4_0||GLEW_VERSION_4_1)
	{
		fprintf(stdout, "OpenGL 4.0 is supported\n");
	}

	glViewport(0, 0, wndWidth, wndHeight);

	glfwSetWindowTitle("RRC framework");
	framesPerSec  = 0;
	frameCnt      = 0;
	startTime     = glfwGetTime();
	deltaTime     = 0.001f;
	buffTime      = 0.0f;
	isRunning     = true;
}

GLFWApp::~GLFWApp()
{
	glfwTerminate();
}

void GLFWApp::HandleInput()
{
	isRunning = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	int x = 0;
	int y = 0;
	glfwGetMousePos(&x, &y);
	deltaX = x - midWidth;
	deltaY = y - midHeight;
	glfwSetMousePos(midWidth, midHeight);
}
void GLFWApp::UpdateVideo()
{
	glfwSwapBuffers();
	frameCnt++;
	if (buffTime>1.0f)
	{
		buffTime = 0.0f;
		framesPerSec = frameCnt;
		frameCnt = 0;
		char str[30];
		sprintf(str,"%s fps:%d", "RRC framework", framesPerSec);
		glfwSetWindowTitle(str);
	}
	double lastTime = glfwGetTime();
	deltaTime = lastTime - startTime;
	buffTime += deltaTime;
	startTime = lastTime;
}
bool GLFWApp::KeepRunning()
{
	return isRunning;
}

float GLFWApp::GetDeltaTime()
{
	return deltaTime;
}
int GLFWApp::GetFPS()
{
	return framesPerSec;
}

bool GLFWApp::GetKey(int key)
{
	return (glfwGetKey(key)==GLFW_PRESS);
}

int GLFWApp::GetMouseWheel()
{
	return glfwGetMouseWheel();
}

void GLFWApp::SetCursorVisible(bool b)
{
	if (!b)
		glfwDisable(GLFW_MOUSE_CURSOR);
	else
		glfwEnable(GLFW_MOUSE_CURSOR);
}

int GLFWApp::GetDeltaX()
{
	return deltaX;
}
int GLFWApp::GetDeltaY()
{
	return deltaY;
}
