/*
 * SDL_App.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "SDL_App.hpp"
#include <iostream>

SDLApp::SDLApp()
{
	putenv(strdup("SDL_VIDEO_CENTERED=1"));
	wnd_width  = 800;
	wnd_height = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(wnd_width, wnd_height, 32, SDL_SWSURFACE);

	SDL_WM_SetCaption("RRC framework", NULL);

	isRunning     = true;
	framesPerSec  = 0;
	frameCnt      = 0;
	timer         = SDL_GetTicks()+1000;
	startTime     = float(SDL_GetTicks())/1000.0f;
	deltaTime     = 0.001f;
}

SDLApp::~SDLApp()
{
	SDL_Quit();
}

SDL_Surface* SDLApp::GetSurface()
{
	return screen;
}

void SDLApp::HandleInput()
{
	std::cout<<"working..."<<std::endl;
	SDL_Event e;
	bool found = false;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_KEYDOWN:
			found = false;
			for(std::vector<int>::iterator it = this->keys.begin();
				it!=this->keys.end();
				++it)
				if (*it==e.key.keysym.sym) { found = true; break;}
			if (found == false)
				keys.push_back(e.key.keysym.sym);
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
				return;
			}
			break;
		case SDL_KEYUP:
			for(std::vector<int>::iterator it = this->keys.begin();
				it!=this->keys.end();
				++it)
				if (*it==e.key.keysym.sym) { keys.erase(it); break;}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
}

void SDLApp::UpdateVideo()
{
	SDL_Flip(screen);

	++frameCnt;
	Uint32 now = SDL_GetTicks();
	if (now>timer)
	{
		timer = now + 1000;
		framesPerSec = frameCnt;
		frameCnt = 0;
		char str[30];
		sprintf(str,"%s fps:%d", "RRC framework", framesPerSec);
		SDL_WM_SetCaption(str, NULL);
	}
	float  lastTime  = float(now)/1000.0f;
	deltaTime = lastTime - startTime;
	startTime = lastTime;
}

bool SDLApp::KeepRunning()
{
	return isRunning;
}

void SDLApp::SetStartTime()
{
}

float SDLApp::GetDeltaTime()
{
	return deltaTime;
}

int SDLApp::GetFPS()
{
	return framesPerSec;
}

bool SDLApp::GetKey(int key)
{
	for(std::vector<int>::iterator it = keys.begin();
		it != keys.end();
		++it)
		if (*it==key) return true;
	return false;
}

int SDLApp::GetMouseWheel()
{
	return -1;
}
