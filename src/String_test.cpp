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
//String str_4 = { 'H','e','l','l','o' }; // list initializer construction
	// Using strings
// access and modify:
// stream output and input
std::cout << str_3;
str.swap(str_3);
cout << str.get_length() << endl; 
cout << str << '\t' << str_3 << '\t' <<  str.pop_back()<< endl;
	cout << str.get_length();
	for(int i = 0; i<str.get_length() ; ++i)
	{
	cout << str[i] << endl;
	} 
return 0;
}
