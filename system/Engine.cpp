/*
 * Engine.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#include "Engine.hpp"

Engine::Engine()
{
	SDLApp::GetInstance();
	isRunning = true;
}

Engine::~Engine()
{
	SDLApp::KillInstance();
}

bool Engine::KeepRunning()
{
	return SDLApp::GetInstance().KeepRunning();
}

void Engine::Update()
{
}

void Engine::Render()
{
}

void Engine::HandleInput()
{
	SDLApp::GetInstance().HandleInput();
}

void Engine::UpdateVideo()
{

}

void Engine::Exit()
{
	isRunning = false;
}
