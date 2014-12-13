#include <iostream>
#include "String.h"

using namespace std;

int main()
{
	//Creating strings - required:
String str = "C-style string literal"; // is the same as: String str("C-style string literal");
String str_2(str);
String str_3 = "moikka";
cout << str_3;
//Optional - not required:
String str_4 = { 'H','e','l','l','o' }; // list initializer construction
cout << str_4 << endl;
	// Using strings
// access and modify:
// stream output and input
String str_empty;

if(str_empty.empty()) cout << "im empty\n";

String str_pop = "moikka";

for(int i = 0; i < 6; ++i) { str_pop.pop_back(); cout << "Popped: " << str_pop << "\tSize is now: " << str_pop.size() << endl; }

str_pop = "moikka";
str_pop.insert(6," kaikki");
cout << str_pop << endl;
/*
String str_in;
cin >> str_in;
cout << str_in.size() << endl;
*/

std::cout << str_3 << endl;
str.swap(str_3);

return 0;
}
