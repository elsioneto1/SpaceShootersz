#ifndef _UFOPOOLMANAGER_H_
#define _UFOPOOLMANAGER_H_
#pragma once

#include <vector>
#include "UFOController.h"

class UFOPoolManager
{

	

public:

	// where all the ufos are stored
	// had to make this separated class because making singleton with the components was giving me a huge headache
	inline static UFOPoolManager& Instance()
	{
		static UFOPoolManager instance;
		return instance;
	}

	std::vector<UFOController*> ufoPool;
	UFOPoolManager();
	~UFOPoolManager();

};


#endif
