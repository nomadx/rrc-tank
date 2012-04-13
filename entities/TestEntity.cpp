/*
 * TestEntity.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "TestEntity.hpp"
#include "../system/GLFW_App.hpp"
#include "../util/Util.hpp"
#include "GL/glfw.h"

TestEntity::TestEntity(AbstractState* pState)
{
	state  = pState;
	locationX = 0.0f;
	locationY = 0.0f;
	speed = 50.0f;
	up    = false;
	down  = false;
	left  = false;
	right = false;
}

TestEntity::~TestEntity()
{
}

void TestEntity::Update()
{
	char str[30];
	if (up)
	{
		locationY -= speed * APP.GetDeltaTime();
		sprintf(str, "UP");
	}
	if (down)
	{
		locationY += speed * APP.GetDeltaTime();
		sprintf(str, "DOWN");
	}
	if (left)
	{
		locationX -= speed * APP.GetDeltaTime();
		sprintf(str, "LEFT");
	}
	if (right)
	{
		locationX += speed * APP.GetDeltaTime();
		sprintf(str, "RIGHT");
	}
	glfwSetWindowTitle(str);
}
void TestEntity::Render()
{
}

void TestEntity::MoveUp(bool b)
{
	up = b;
}
void TestEntity::MoveDown(bool b)
{
	down = b;
}
void TestEntity::MoveLeft(bool b)
{
	left = b;
}
void TestEntity::MoveRight(bool b)
{
	right = b;
}
