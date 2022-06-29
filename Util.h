#pragma once
#ifndef UTIL_H
#define UTIL_H
#include <random>
#include "BlockTemplate.h"
#include "GLOBAL.h"
class Util
{
	std::random_device rd;
	std::mt19937 gen;
	Util();
	static Util* Instance;

	public:
		void LoadBlocks();
		Util(Util& other) = delete;
		void operator=(const Util&) = delete;
		static	Util* GetInstance();
	float random(int min, int max);
		std::vector<BlockTemplate> BLOCKS;


};


#endif // !UTIL_H
