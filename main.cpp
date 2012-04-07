/*
 * main.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: Sharavsambuu
 */
#include <iostream>
#include "system/Engine.hpp"
#include "game/Intro.hpp"
/*#include "game/Menu.hpp"
#include "game/Game.hpp"
#include "game/End.hpp"
*/

int main(int argc, char **argv)
{

	Engine *game = new Engine();

	Intro *intro = new Intro();
	game->AddGameState(intro);
/*	game->AddGameState(new Intro());
	game->AddGameState(new Menu());
	game->AddGameState(new Game());
	game->AddGameState(new End());
*/

	while(game->KeepRunning())
	{
		game->Update();
		game->Render();
		game->HandleInput();
		game->UpdateVideo();
		std::cout<<"test.."<<std::endl;
	}

	delete intro;
	delete game;
	intro = 0;
	game  = 0;
	return 0;
}
