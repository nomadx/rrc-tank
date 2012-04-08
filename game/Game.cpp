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
}

Game::~Game()
{
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
}
void Game::Render()
{
	SDL_FillRect(SDLAPP.GetSurface(), NULL , 0x221122);
//	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
