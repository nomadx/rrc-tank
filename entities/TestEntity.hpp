/*
 * TestEntity.hpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#ifndef TESTENTITY_HPP_
#define TESTENTITY_HPP_

#include "IEntity.hpp"
#include "../game/AbstractState.hpp"
#include "SDL/SDL.h"
#include "../util/ImageLoader.hpp"

class TestEntity : public IEntity
{
public :
	TestEntity(AbstractState* pState);
	~TestEntity();

	void Update();
	void Render();

	void MoveUp   (bool b);
	void MoveDown (bool b);
	void MoveLeft (bool b);
	void MoveRight(bool b);

protected:
private:
	AbstractState* state;

	SDL_Surface* sprite;
	float locationX;
	float locationY;
	float speed;

	bool up;
	bool down;
	bool left;
	bool right;
};

#endif /* TESTENTITY_HPP_ */
