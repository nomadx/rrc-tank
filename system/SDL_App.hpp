/*
 * SDL_App.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef SDL_APP_HPP_
#define SDL_APP_HPP_
#include "../util/Singleton.hpp"
#include <vector>
#include "SDL/SDL.h"

class SDLApp : public Singleton<SDLApp>
{
	friend class Singleton<SDLApp>;
public:
	SDLApp();
	~SDLApp();

	SDL_Surface* GetSurface();

	void HandleInput();
	void UpdateVideo();
	bool KeepRunning();

	void  SetStartTime();
	float GetDeltaTime();
	int   GetFPS();

	bool GetKey(int key);
	int  GetMouseWheel();

protected:
private:
	bool  isRunning;
	float startTime;
	float deltaTime;
	int   framesPerSec;
	int   frameCnt;
	Uint32 timer;

	std::vector<int> keys;
	int  mouseWheel;
	bool mouseCentered;

	int wnd_width;
	int wnd_height;
	SDL_Surface* screen;
};

#endif /* SDL_APP_HPP_ */
