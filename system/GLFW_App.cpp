/*
 * GLFW_App.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#include "GLFW_App.hpp"
#include "stdlib.h"
#include <stdio.h>

GLFWApp::GLFWApp()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	wnd_width  = 800;
	wnd_height = 600;
	int redBits   = 8, greenBits = 8,  blueBits    = 8;
	int alphaBits = 8, depthBits = 24, stencilBits = 8;
	if (!glfwOpenWindow(wnd_width,wnd_height,redBits,greenBits,blueBits,alphaBits,depthBits,stencilBits,GLFW_WINDOW))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
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
		/*char str[30];
		sprintf(str,"%s fps:%d", "RRC framework", framesPerSec);
		glfwSetWindowTitle(str);*/
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
