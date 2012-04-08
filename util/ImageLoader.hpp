/*
 * ImageLoade.hpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#ifndef IMAGELOADE_HPP_
#define IMAGELOADE_HPP_

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *load_image(std::string filename);

#endif /* IMAGELOADE_HPP_ */
