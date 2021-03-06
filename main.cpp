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
#include "game/Demo02.hpp"
#include "game/Demo03.hpp"
#include "game/Demo04.hpp"
#include "game/TankDemo.hpp"

int main(void)
{
	int x = 5;
	ASSERT(x==5);
	//ASSERT(x!=5);

	Engine *engine = Engine::Instance();

	engine->AddGameState("intro" , new Intro());
	engine->AddGameState("game"  , new Game());
	engine->AddGameState("demo00", new Demo00());
	engine->AddGameState("demo01", new Demo01());
	engine->AddGameState("demo02", new Demo02());
	engine->AddGameState("demo03", new Demo03());
	engine->AddGameState("demo04", new Demo04());
	engine->AddGameState("tankDemo", new TankDemo());

	engine->ChangesState("tankDemo");

	while(engine->KeepRunning())
	{
		engine->Update();
		engine->Render();
		engine->HandleInput();
		engine->UpdateVideo();
	}

	return 0;
}
