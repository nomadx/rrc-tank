/*
 * Game.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "Game.hpp"
#include "../util/ImageLoader.hpp"

Game::Game()
{
	background = load_image("data/background.png");
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
	SDL_FreeSurface(background);
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
		enteredTime += SDLAPP.GetDeltaTime();
		if (enteredTime>0.5f)
		{
			isEntered   = false;
			enteredTime = 0.0;
		}
	}

	bool spaceButton = SDLAPP.GetKey(SDLK_SPACE);
	if (spaceButton&&!isEntered)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("intro");
	}

	tank->MoveUp   (SDLAPP.GetKey(SDLK_UP)   ||SDLAPP.GetKey(SDLK_w));
	tank->MoveDown (SDLAPP.GetKey(SDLK_DOWN) ||SDLAPP.GetKey(SDLK_s));
	tank->MoveLeft (SDLAPP.GetKey(SDLK_LEFT) ||SDLAPP.GetKey(SDLK_a));
	tank->MoveRight(SDLAPP.GetKey(SDLK_RIGHT)||SDLAPP.GetKey(SDLK_d));

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Update();
	}
}
void Game::Render()
{
	SDL_FillRect(SDLAPP.GetSurface(), NULL , 0x221122);

	for (unsigned int i=0; i<entities.size(); i++)
	{
		IEntity* entity = entities[i];
		entity->Render();
	}
//	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
