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
#include <iostream>
using namespace std;

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#define DEBUG
#ifndef DEBUG
	#define ASSERT(x)
#else
	#define ASSERT(x) \
		if (! (x)) \
		{ \
			cout << "ERROR!! Assert " << #x << " failed. "; \
			cout << __FILE__ << " : " << __LINE__ << "\n"; \
		}
#endif

#define ENGINE Engine    ::GetInstance()
#define APP    GLFWApp   ::GetInstance()
#define LOG    LogManager::GetInstance()

#endif /* UTIL_HPP_ */
