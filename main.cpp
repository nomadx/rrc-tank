/*
 * main.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: Sharavsambuu
 *
 */

#include <iostream>
#include "util/Util.hpp"
#include "system/Engine.hpp"
#include "game/Intro.hpp"
#include "game/Game.hpp"
#include "game/Demo00.hpp"
#include "game/Demo01.hpp"

int main(void)
{
	int x = 5;
	ASSERT(x==5);
	ASSERT(x!=5);

	Engine *engine = Engine::Instance();

	engine->AddGameState("intro", new Intro());
	engine->AddGameState("game" , new Game());
	engine->AddGameState("demo00", new Demo00());
	engine->AddGameState("demo01", new Demo01());

	engine->ChangesState("demo01");

	while(engine->KeepRunning())
	{
		engine->Update();
		engine->Render();
		engine->HandleInput();
		engine->UpdateVideo();
	}

	return 0;
}
