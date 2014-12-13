#include <iostream>
#include "String.h"

using namespace std;

int main()
{
	//Creating strings - required:
String str = "C-style string literal"; // is the same as: String str("C-style string literal");
String str_2(str);
String str_3 = "moi";
//Optional - not required:
String str_4 = { 'H','e','l','l','o' }; // list initializer construction
cout << str_4 << endl;
	// Using strings
// access and modify:
// stream output and input
String str_empty;

if(str_empty.empty()) cout << "im empty\n";

std::cout << str_3;
str.swap(str_3);

return 0;
}
