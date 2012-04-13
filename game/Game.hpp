/*
 * Game.hpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "AbstractState.hpp"
#include "../system/Engine.hpp"
#include "../entities/IEntity.hpp"
#include "../entities/TestEntity.hpp"

class Game : public AbstractState
{
public:
	Game();
	~Game();

	void Pause();
	void Resume();

	void Update();
	void Render();

protected:
private:
	bool isEntered;
	float enteredTime;

	std::vector<IEntity*> entities;
	TestEntity* tank;
};


#endif /* GAME_HPP_ */
