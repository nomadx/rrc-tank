/*
 * Engine.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#include "Engine.hpp"

Engine::Engine()
{
	isRunning = true;
}

Engine::~Engine()
{
}

bool Engine::keepRunning()
{
	return isRunning;
}

void Engine::Update()
{
}

void Engine::Render()
{
}

void Engine::HandleInput()
{
}

void Engine::UpdateVideo()
{
}

void Engine::Exit()
{
	isRunning = false;
}
