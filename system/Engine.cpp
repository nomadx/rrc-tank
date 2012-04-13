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
	APP;
	LOG;
	isRunning = true;
}

Engine::~Engine()
{
	for(std::map<std::string, AbstractState*>::iterator it = states.begin();
		it != states.end();
		++it)
	{
		delete (*it).second;
	}
	states.clear();
	GLFWApp   ::KillInstance();
	LogManager::KillInstance();
}

bool Engine::KeepRunning()
{
	return APP.KeepRunning();
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
	APP.HandleInput();
}

void Engine::UpdateVideo()
{
	APP.UpdateVideo();
}

void Engine::AddGameState(const std::string& name, AbstractState* state)
{
	std::map<std::string, AbstractState*>::iterator it = states.find(name);
	if (it==states.end())
	{
		states[name] = state;
	}
}

void Engine::ChangesState(const std::string& name)
{
	std::map<std::string, AbstractState*>::iterator it = states.find(name);
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
