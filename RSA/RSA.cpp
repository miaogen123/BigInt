#include "pch.h"
#include "DebugMode.h"
#include <iostream>

#include <fstream>
#include "bigInt.h"
#include"myutils.h"
//#define DEBUG_ADD_MINUS

void TestAddMinus()
{
	bigInt hel1{};
	bigInt hel2{};
	std::ofstream testDataOut("test.txt", std::fstream::app);
	for (int i = 0; i < 1000; i++) {
		//uint64_t a = getRandomInt();
		//uint64_t b = getRandomInt();
		//hel1.set(std::to_string(a));
		//hel2.set(std::to_string(b));
		std::string a, b;
		for (int j = 0; j < 400; j++) {
			if (j == 0) {
				if (getRandomInt() % 2 == 0)
					a.push_back('+');
				else
					a.push_back('-');
			}
			a.push_back(static_cast<char>(getRandomInt(48, 57)));
		}
		for (int j = 0; j < 400; j++) {
			if (j == 0) {
				if (getRandomInt() % 2 == 0)
					b.push_back('+');
				else
					b.push_back('-');
			}
			b.push_back(static_cast<char>(getRandomInt(48, 57)));
		}
		hel1.set(a);
		hel2.set(b);
		testDataOut << a<<std::endl;
		testDataOut << b<<std::endl;
		auto val = hel1 + hel2;
		testDataOut << (hel1-hel2).getWithSign() << std::endl;
		testDataOut << (hel1+hel2).getWithSign() << std::endl;
	}
	testDataOut.close();
}

int main()
{
	bigInt hel1{};
	bigInt hel2{};

#ifdef DEBUG_ADD_MINUS
	TestAddMinus();
#endif // DEBUG_ADD_MINUS

	return 0;
}
