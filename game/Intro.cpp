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
	isEntered = true;
}

Intro::~Intro()
{
	SDL_FreeSurface(background);
}

void Intro::Pause()
{
	isEntered = false;
}
void Intro::Resume()
{
	isEntered   = true;
	enteredTime = 0.0f;
}

void Intro::Update()
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
		engine->ChangesState("game");
	}
}
void Intro::Render()
{
	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
