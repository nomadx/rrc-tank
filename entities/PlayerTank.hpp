/*
 * PlayerTank.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef PLAYERTANK_HPP_
#define PLAYERTANK_HPP_

#include "IEntity.hpp"

class PlayerTank : public IEntity
{
public:
	PlayerTank();
	~PlayerTank();

	virtual void Update();
	virtual void Render();
};

#endif /* PLAYERTANK_HPP_ */
