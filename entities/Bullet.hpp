/*
 * Bullet.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "IEntity.hpp"

class Bullet : public IEntity
{
public:
	Bullet();
	~Bullet();

	virtual void Update();
	virtual void Render();
};

#endif /* BULLET_HPP_ */
