/*
 * Intro.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "Intro.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"
#include "../util/ImageLoader.hpp"

Intro::Intro()
{
	SDL_Surface* temp = load_image("data/intro.png");
	background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	fader = SDL_CreateRGBSurface( SDL_SRCALPHA,
			background->w, background->h,
			background->format->BitsPerPixel,
			background->format->Rmask, background->format->Gmask,
			background->format->Bmask, background->format->Amask );
	SDL_FillRect (fader, NULL, SDL_MapRGB (background->format, 0, 0, 0)) ;
	alpha = 255;
	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

	isEntered = true;
}

Intro::~Intro()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(fader);
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

	alpha--;
	if (alpha < 0)
		alpha = 0;
	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);
}
void Intro::Render()
{
	SDL_BlitSurface(background, NULL, SDLAPP.GetSurface(), NULL);
	if (alpha!=0)
		SDL_BlitSurface(fader, NULL, SDLAPP.GetSurface(), NULL);
	SDL_UpdateRect(SDLAPP.GetSurface(), 0, 0, 0, 0);
}
