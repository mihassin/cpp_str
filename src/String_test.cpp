#include <iostream>
#include "String.h"

using namespace std;

// type conversions 
// Required: const char* -> String
void f(String s) 
{
 //...
}


int main()
{

String str = "moi";
str.insert(3, " kaikki");
cout << str << endl;

str.erase(5,9);
str.clear();
str = "moi";
String str1 = " kaikki";

cout << "pakki"+str << endl << str.size();
return 0;
}
