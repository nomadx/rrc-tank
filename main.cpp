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
/*#include "game/Menu.hpp"
#include "game/Game.hpp"
#include "game/End.hpp"
*/

int main(int argc, char **argv)
{
	Engine *engine = Engine::Instance();
	//engine->SetTitle("RRC framework");

	Intro *intro = new Intro();
	engine->AddGameState("intro", intro);
/*	game->AddGameState(new Intro());
	game->AddGameState(new Menu());
	game->AddGameState(new Game());
	game->AddGameState(new End());
*/
	engine->ChangesState("intro");

	while(engine->KeepRunning())
	{
		engine->Update();
		engine->Render();
		engine->HandleInput();
		engine->UpdateVideo();
	}

	delete intro;
	intro  = 0;

	return 0;
}
