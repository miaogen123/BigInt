#include"pch.h"
#include "myutils.h"
#include<chrono>
//#include<unistd.h>


const  int getRandomInt( int min , int max)
{
	//errror
	//std::default_random_engine e(std::chrono::high_resolution_clock::to_time_t(std::chrono::high_resolution_clock::now())+static_cast<long long>((&temp))&65535 );


	std::random_device rd;
	std::mt19937 gen(rd());
	//std::default_random_engine e();
	std::uniform_int_distribution<unsigned int> uig(min, max);
	return uig(gen);

	//srand(std::chrono::high_resolution_clock::to_time_t(std::chrono::high_resolution_clock::now()));
	//return static_cast<int>(rand());
}
