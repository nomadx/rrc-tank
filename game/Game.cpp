/*
 * Game.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "Game.hpp"

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
	//SDL_FreeSurface(background);
}

void Game::Pause()
{
	isEntered = false;
}
void Game::Resume()
{
	isEntered   = true;
	enteredTime = 0.0f;
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

	bool spaceButton = APP.GetKey(GLFW_KEY_SPACE);
	if (spaceButton&&!isEntered)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("intro");
	}

	tank->MoveUp   (APP.GetKey(GLFW_KEY_UP)   );
	tank->MoveDown (APP.GetKey(GLFW_KEY_DOWN) );
	tank->MoveLeft (APP.GetKey(GLFW_KEY_LEFT) );
	tank->MoveRight(APP.GetKey(GLFW_KEY_RIGHT));

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Update();
	}
}
void Game::Render()
{
	//SDL_FillRect(SDLAPP.GetSurface(), NULL , 0x221122);

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Render();
	}
//	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
