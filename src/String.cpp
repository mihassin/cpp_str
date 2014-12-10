#include <iostream>
#include "String.h"

//strlen equivalent
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
}

//String from String reference
String::String(const String& str)
{
	length = str.get_length();
}

//destructor
String::~String()
{
  delete []characters;
  length = 0;
}
