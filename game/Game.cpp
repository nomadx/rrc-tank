/*
 * Game.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "Game.hpp"

Game::Game()
{
	background = SDL_LoadBMP("data/gamestate.bmp");
}

Game::~Game()
{
	SDL_FreeSurface(background);
}

void Game::Pause()
{
}
void Game::Resume()
{
}

void Game::Update()
{
	bool spaceButton = SDLAPP.GetKey(SDLK_SPACE);
	if (spaceButton)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("intro");
	}
}
void Game::Render()
{
	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
