/*
 * SDL_App.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "SDL_App.hpp"

SDLApp::SDLApp()
{
	wnd_width  = 800;
	wnd_height = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(wnd_width, wnd_height, 32, SDL_SWSURFACE);

	isRunning = true;
}

SDLApp::~SDLApp()
{
	SDL_Quit();
}

void SDLApp::HandleInput()
{
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
	return -1;
}

int SDLApp::GetFPS()
{
	return 30;
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
