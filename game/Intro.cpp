/*
 * Intro.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "Intro.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"

Intro::Intro()
{
	background = SDL_LoadBMP("data/screen.bmp");
}

Intro::~Intro()
{
	SDL_FreeSurface(background);
}

void Intro::Pause()
{
}
void Intro::Resume()
{
}

void Intro::Update()
{
	bool spaceButton = SDLAPP.GetKey(SDLK_SPACE);
	if (spaceButton)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("game");
	}
}
void Intro::Render()
{
	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
