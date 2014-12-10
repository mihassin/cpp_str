#include <iostream>
#include "String.h"

/*
   strlen equivalent
   arg: const char* p
   counts char-arrays elements
   result: number of elements in given char-array
*/
int strlen(const char* p)
{
	int count = 0;
	while(*p) { ++count; ++p; }
	return count;
}

//default constructor
String::String()
{
  length = 0;
  characters = new char[1];
  characters[1] = '\0';
}

//String from char array
String::String(const char* chars)
{
	length = strlen(chars);
	characters = new char[length+1];
	//coping the values
	for(int i = 0; i<=length; ++i) { characters[i] = chars[i]; }
	//last character of string is the null char '\0'
	characters[length] = '\0';
}

//String from String reference
String::String(const String& str)
{
	length = str.get_length();
	characters = new char[length+1];	
	for(int i = 0; i<=length; ++i) { characters[i] = str[i]; }
	characters[length] = '\0';
}

//destructor
String::~String()
{
  delete []characters;
  length = 0;
}

// overloaded operator<<
std::ostream& operator<<(std::ostream& os, const String& str) { return os << str.characters; }
