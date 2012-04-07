/*
 * Intro.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "Intro.hpp"
#include "../util/Util.hpp"

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
}
void Intro::Render()
{
	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
}
