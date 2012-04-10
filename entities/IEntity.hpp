/*
 * IEntity.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

class IEntity
{
public :
	IEntity();
	virtual ~IEntity();

	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif /* IENTITY_HPP_ */
