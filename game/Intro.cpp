/*
 * Intro.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "Intro.hpp"
#include "../util/Util.hpp"
#include "../system/Engine.hpp"

Intro::Intro()
{
	isEntered = true;
}

Intro::~Intro()
{
}

void Intro::Pause()
{
	isEntered = false;
}
void Intro::Resume()
{
	isEntered   = true;
	enteredTime = 0.0f;
}

void Intro::Update()
{
	if (isEntered)
	{
		enteredTime += APP.GetDeltaTime();
		if (enteredTime>0.5f)
		{
			isEntered   = false;
			enteredTime = 0.0;
		}
	}
	bool spaceButton = APP.GetKey(GLFW_KEY_SPACE);
	if (spaceButton&&!isEntered)
	{
		Engine *engine = Engine::Instance();
		engine->ChangesState("game");
	}

}
void Intro::Render()
{
}
