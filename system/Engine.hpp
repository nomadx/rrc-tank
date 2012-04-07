/*
 * Engine.hpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <map>
#include <string>
#include "SDL_App.hpp"
#include "LogManager.hpp"
#include "../game/AbstractState.hpp"
#include "../util/Util.hpp"

class Engine
{
public:
	Engine();
	~Engine();

	bool KeepRunning();

	void Update();
	void Render();
	void HandleInput();
	void UpdateVideo();

	void AddGameState(const std::string& name, AbstractState* state);
	void ChangesState(const std::string& name);

	void Exit();

	static Engine* Instance() {
		return &engineInstance;
	}

protected:
private:
	static Engine engineInstance;

	bool isRunning;
	AbstractState* currentState;
	std::map<std::string, AbstractState*> states;
};

#endif /* ENGINE_HPP_ */
