/*
 * main.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: Sharavsambuu
 */

#include "system/Engine.hpp"
#include "game/Intro.hpp"
#include "game/Menu.hpp"
#include "game/Game.hpp"
#include "game/End.hpp"

int main(int argc, char **argv)
{
	Engine *game = new Engine();

/*	Intro intro;
	game->AddGameState(&intro);
	game->AddGameState(new Intro());
	game->AddGameState(new Menu());
	game->AddGameState(new Game());
	game->AddGameState(new End());
*/

	while(game->keepRunning())
	{
		game->Update();
		game->Render();
		game->HandleInput();
		game->UpdateVideo();
	}
	delete game;
	game = 0;
	return 0;
}
