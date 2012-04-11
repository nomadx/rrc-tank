/*
 * GLFW_App.hpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#ifndef GLFW_APP_HPP_
#define GLFW_APP_HPP_

#include "../util/Singleton.hpp"
#include <vector>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/glfw.h"


class GLFWApp : public Singleton<GLFWApp>
{
	friend class Singleton<GLFWApp>;
public:
	GLFWApp();
	~GLFWApp();

	void HandleInput();
	void UpdateVideo();
	bool KeepRunning();

	float GetDeltaTime();
	int   GetFPS();

	bool GetKey(int key);
	int  GetMouseWheel();

protected:
private:
	bool   isRunning;
	double startTime;
	double deltaTime;
	double buffTime;
	int    framesPerSec;
	int    frameCnt;

	std::vector<int> keys;
	int  mouseWheel;
	bool mouseCentered;

	int wnd_width;
	int wnd_height;
};

#endif /* GLFW_APP_HPP_ */
