#include <iostream>
#include "getindex.h"



int main(int, char**)
{
	typedef TypeList<char, short, int, long> IntegerTypes;
	char const * f= "short";
	TypeSwitch<IntegerTypes> ts;

	
	std::cout << ts.getIndexOf(f);
	system("pause");
	return 0;
}