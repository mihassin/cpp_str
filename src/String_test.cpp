#include <iostream>
#include "String.h"

using namespace std;

int main()
{
	//Creating strings - required:
String str = "C-style string literal"; // is the same as: String str("C-style string literal");
String str_2(str);
String str_3;
//Optional - not required:
//String str_4 = { 'H','e','l','l','o' }; // list initializer construction
	// Using strings
// access and modify:
// stream output and input
std::cout << str_3;
String input_str;
std::cin >> input_str;
cout<<input_str;
	return 0;
}
