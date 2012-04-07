/*
 * Engine.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#include "Engine.hpp"

Engine Engine::engineInstance;

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
	currentState->Update();
}

void Engine::Render()
{
	currentState->Render();
}

void Engine::HandleInput()
{
	std::cout<<"handling input"<<std::endl;
	SDLAPP.HandleInput();
}

void Engine::UpdateVideo()
{

}

void Engine::AddGameState(const std::string& name, AbstractState* state)
{
	std::map<std::string,AbstractState*>::iterator it = states.find(name);
	if (it==states.end())
	{
		states[name] = state;
	}
}

void Engine::ChangesState(const std::string& name)
{
	std::map<std::string,AbstractState*>::iterator it = states.find(name);
	if (it!=states.end())
	{
		if (currentState)
			currentState->Pause();
		currentState = states[name];
		currentState->Resume();
	}
}

void Engine::Exit()
{
	isRunning = false;
}
