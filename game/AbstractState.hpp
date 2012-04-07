/*
 * AbstractState.hpp
 *
 *  Created on: Apr 6, 2012
 *      Author: sharavsambuu
 */

#ifndef ABSTRACTSTATE_HPP_
#define ABSTRACTSTATE_HPP_

class AbstractState
{
public:
	AbstractState();
	virtual ~AbstractState();

	virtual void Pause () = 0;
	virtual void Resume() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

};

#endif /* ABSTRACTSTATE_HPP_ */
