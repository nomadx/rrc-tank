/*
 * ImageLoader.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: sharavsambuu
 */

#include "ImageLoader.hpp"

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface( loadedImage );
    }
    return optimizedImage;
}
