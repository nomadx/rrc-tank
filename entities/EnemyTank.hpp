/*
 * EnemyTank.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef ENEMYTANK_HPP_
#define ENEMYTANK_HPP_

#include "IEntity.hpp"

class EnemyTank : public IEntity
{
public:
	EnemyTank();
	~EnemyTank();

	virtual void Update();
	virtual void Render();
};

#endif /* ENEMYTANK_HPP_ */
