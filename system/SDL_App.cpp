/*
 * SDL_App.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "SDL_App.hpp"

SDLApp::SDLApp()
{
}

SDLApp::~SDLApp()
{
}

void SDLApp::HandleInput()
{
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
	return false;
}

int SDLApp::GetMouseWheel()
{
	return -1;
}
