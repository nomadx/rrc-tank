/*
 * Game.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "Game.hpp"
#include "stdio.h"

Game::Game()
{
	isEntered = true;

	tank = new TestEntity(this);
	entities.push_back(tank);
}

Game::~Game()
{
	for (unsigned int i=0; i<entities.size();i++)
	{
		IEntity* entity = entities[i];
		entities[i] = 0;
		delete entity;
	}
	entities.clear();
}

void Game::Pause()
{
	isEntered = false;
}
void Game::Resume()
{
	isEntered   = true;
	enteredTime = 0.0f;

	char str[30];
	sprintf(str, "entered Game state.");
	glfwSetWindowTitle(str);

	APP.SetCursorVisible(true);
}

void Game::Update()
{
	if (isEntered)
	{
		enteredTime += APP.GetDeltaTime();
		if (enteredTime>0.5f)
		{
			isEntered   = false;
			enteredTime = 0.0;
		}
	}

	bool changeButton = APP.GetKey(GLFW_KEY_F1);
	if (changeButton&&!isEntered)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("intro");
	}

	tank->MoveUp   (APP.GetKey(GLFW_KEY_UP)   ||APP.GetKey('W'));
	tank->MoveDown (APP.GetKey(GLFW_KEY_DOWN) ||APP.GetKey('S'));
	tank->MoveLeft (APP.GetKey(GLFW_KEY_LEFT) ||APP.GetKey('A'));
	tank->MoveRight(APP.GetKey(GLFW_KEY_RIGHT)||APP.GetKey('D'));

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Update();
	}
}
void Game::Render()
{
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Render();
	}
}
