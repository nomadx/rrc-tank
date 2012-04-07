/*
 * Game.hpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "AbstractState.hpp"

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
};


#endif /* GAME_HPP_ */
