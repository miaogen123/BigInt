#include "pch.h"
#include "DebugMode.h"
#include <iostream>

#include <fstream>
#include "bigInt.h"
#include"myutils.h"
//#define DEBUG_ADD_MINUS
//#define DEBUG_MULTI
#define DEBUG_EQUAL

enum class Arithmetic_Operation {
	Add,
	Minus,
	Multi,
	Divide,
};


void TestOperator(const Arithmetic_Operation& operat, const std::string& filename)
{
	bigInt hel1{};
	bigInt hel2{};
	std::ofstream testDataOut(filename, std::fstream::app);
	for (int i = 0; i < 10000; i++) {
		std::string a, b;
		int up1 = getRandomInt(1, 400);
		int up2 = getRandomInt(1, 400);
		for (int j = 0; j < up1; j++) {
			if (j == 0) {
				if (getRandomInt() % 2 == 0)
					a.push_back('+');
				else
					a.push_back('-');
			}
			a.push_back(static_cast<char>(getRandomInt(48, 57)));
		}
		for (int j = 0; j < up2; j++) {
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
		testDataOut << hel1.getWithSign()<<std::endl;
		testDataOut << hel2.getWithSign()<<std::endl;
		bigInt result{ "0" };
		std::tuple<bigInt, bigInt> resultOfTwo;
		switch (operat)
		{
		case Arithmetic_Operation::Add:
			result = hel1 + hel2; 
			testDataOut << result.getWithSign() << std::endl;
			break;
		case Arithmetic_Operation::Minus:
			result = hel1 - hel2;
			testDataOut << result.getWithSign() << std::endl;
			break;
		case Arithmetic_Operation::Multi:
			result = hel1 * hel2;
			testDataOut << result.getWithSign() << std::endl;
			break;
		case Arithmetic_Operation::Divide:
			resultOfTwo = hel1 / hel2;
			result = std::get<0>(resultOfTwo);
			break;
		default:
			break;
		}
		testDataOut << result.getWithSign() << std::endl;
	}
	testDataOut.close();
}



int main()
{
	bigInt hel1{};
	bigInt hel2{};
	
	//TestOperator(Arithmetic_Operation::Add, "test.txt");
	//TestOperator(Arithmetic_Operation::Minus, "test.txt");

	//TestOperator(Arithmetic_Operation::Multi, "testMulti.txt");
	TestOperator(Arithmetic_Operation::Divide, "testDivid.txt");



	return 0;
}
