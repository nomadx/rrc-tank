/*
 * TestEntity.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "TestEntity.hpp"
#include "../system/GLFW_App.hpp"
#include "../util/Util.hpp"

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
	if (up)
	{
		locationY -= speed * APP.GetDeltaTime();
	}
	if (down)
	{
		locationY += speed * APP.GetDeltaTime();
	}
	if (left)
	{
		locationX -= speed * APP.GetDeltaTime();
	}
	if (right)
	{
		locationX += speed * APP.GetDeltaTime();
	}
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
