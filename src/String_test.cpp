#include <iostream>
#include "String.h"

int main()
{
	String str = "moi";
	String str1 = "heippa";
	std::cout << str << '\t' << str1 << std::endl;
	String str2 = str1;
	std::cout << str << '\t' << str1 << std::endl;
	return 0;
}
