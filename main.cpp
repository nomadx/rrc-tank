/*
 * main.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: Sharavsambuu
 */

#include <iostream>
#include "util/Util.hpp"
#include "system/Engine.hpp"
#include "game/Intro.hpp"
#include "game/Game.hpp"

int main(void)
{
	int x = 5;
	ASSERT(x==5);
	ASSERT(x!=5);

<<<<<<< HEAD
//	Intro intro;
//	game->AddGameState(&intro);

	//game->AddGameState(new Intro());
	/*game->AddGameState(new Menu());
	game->AddGameState(new Game());
	game->AddGameState(new End());*/
=======
	Engine *engine = Engine::Instance();

	engine->AddGameState("intro", new Intro());
	engine->AddGameState("game" , new Game());
>>>>>>> upstream/master

	engine->ChangesState("intro");

	while(engine->KeepRunning())
	{
		engine->Update();
		engine->Render();
		engine->HandleInput();
		engine->UpdateVideo();
	}

	return 0;
}
