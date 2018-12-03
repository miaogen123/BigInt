
#include "pch.h"
#include "DebugMode.h"
#include <iostream>
#include "bigInt.h"
#include"myutils.h"

int main()
{

	bigInt hel1{};
	bigInt hel2{};
	for (int i = 0; i < 0; i++) {
		uint64_t a = getRandomInt(0, UINT32_MAX);
		uint64_t b = getRandomInt(0, UINT32_MAX);
		hel1.set(std::to_string(a));
		hel2.set(std::to_string(b));
		auto val = hel1 + hel2;
		std::cout << a<< " "<<b<<std::endl;
		std::cout << val.get() << std::endl; 
		std::cout << a+b << std::endl; 
		std::cout << std::endl;
	}
	uint64_t a = getRandomInt(0, UINT32_MAX);
	uint64_t b = getRandomInt(0, UINT32_MAX);
	hel1.set(std::to_string(a));
	hel2.set(std::to_string(b));
	std::cout << a<< " "<<b<<std::endl;
	auto p = hel1 - hel2;
	CDebug(p.get());

	
	return 0;
}

