/*
 * ShaderManager.hpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#ifndef SHADERMANAGER_HPP_
#define SHADERMANAGER_HPP_

#include "../util/Singleton.hpp"

class ShaderManager : public Singleton<ShaderManager>
{
	friend class Singleton<ShaderManager>;
public:
	ShaderManager();
	~ShaderManager();
};


#endif /* SHADERMANAGER_HPP_ */
