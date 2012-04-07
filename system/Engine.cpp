/*
 * Engine.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#include "Engine.hpp"

Engine::Engine()
{
	SDLAPP;
	LOG   ;
	isRunning = true;
}

Engine::~Engine()
{
	SDLApp    ::KillInstance();
	LogManager::KillInstance();
}

bool Engine::KeepRunning()
{
	return SDLAPP.KeepRunning();
}

void Engine::Update()
{
}

void Engine::Render()
{
}

void Engine::HandleInput()
{
	std::cout<<"handling input"<<std::endl;
	SDLAPP.HandleInput();

	bool up   = SDLAPP.GetKey(SDLK_UP)  || SDLAPP.GetKey(SDLK_w);
	bool down = SDLAPP.GetKey(SDLK_DOWN)|| SDLAPP.GetKey(SDLK_s);

	if (up)
	{
		std::cout<<"up"<<std::endl;
	}
	if (down)
	{
		std::cout<<"down"<<std::endl;
	}

}

void Engine::UpdateVideo()
{

}

void Engine::AddGameState(AbstractState* state)
{
}

void Engine::Exit()
{
	isRunning = false;
}
