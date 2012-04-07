/*
 * Engine.hpp
 *
 *  Created on: Apr 4, 2012
 *      Author: sharavsambuu
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include "../game/AbstractState.hpp"

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

	void AddGameState(AbstractState& state);

	void Exit();

protected:
private:
	bool isRunning;
};

#endif /* ENGINE_HPP_ */
