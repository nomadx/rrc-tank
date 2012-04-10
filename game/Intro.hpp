/*
 * Intro.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef INTRO_HPP_
#define INTRO_HPP_

#include "AbstractState.hpp"
#include "../system/Engine.hpp"

class Intro : public AbstractState
{
public:
	Intro();
	~Intro();

	void Pause();
	void Resume();

	void Update();
	void Render();

protected:
private:
	/*SDL_Surface* background;
	SDL_Surface* fader;
	int alpha;*/

	bool isEntered;
	float enteredTime;
};

#endif /* INTRO_HPP_ */
