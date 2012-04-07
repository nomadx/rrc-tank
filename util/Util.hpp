/*
 * Util.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#define ENGINE Engine    ::GetInstance()
#define SDLAPP SDLApp    ::GetInstance()
#define LOG    LogManager::GetInstance()

#endif /* UTIL_HPP_ */
