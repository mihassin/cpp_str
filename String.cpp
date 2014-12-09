//#include <iostream>
#include "String.h"

//default constructor
String::String() 
{
  characters = new char[1];
  characters[1] = '\0';
  length = 0;
}

//String from char array
String::String(char* chars)
{
}

//String from String reference
String::String(const String& str)
{
}

//destructor
String::~String()
{
  delete []characters;
  length = 0;
}
