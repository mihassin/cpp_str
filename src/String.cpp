#include <iostream>
#include "String.h"

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

/* Copy constructor.
   Constructor structure is similar to String::String(const char* chars).
   Only difference is the function arg, which alters few lines.
*/
String::String(const String& str)
{
	length = str.get_length();
	characters = new char[length+1];	
	for(int i = 0; i<=length; ++i) { characters[i] = str[i]; }
	characters[length] = '\0';
}

//Move constructor
String::String(String&& str)
	:length{str.length}, characters{str.characters}
{
	str.length = 0;
	str.characters = nullptr;
}

//copy assignment
String& String::operator=(const String& str)
{
	if(this==&str) return *this;
	
	length = str.get_length();
	char* arr = new char[length+1];		
	for(int i = 0; i<=length; ++i) { arr[i] = str[i]; }
	arr[length] = '\0';
	delete[] characters;
	characters = arr;
	return *this;
}

//move assignment
String& String::operator=(String&& str)
{
	delete[] characters;
	characters = str.characters;
	length = str.length;
	str.characters = nullptr;
	str.length = 0;
	return *this;	
}

/*
   strlen equivalent
   arg: const char* p
   counts char-arrays elements
   result: number of elements in given char-array
*/
int String::strlen(const char* p)
{
	int count = 0;
	while(*p) { ++count; ++p; }
	return count;
}

//push_back
//void String::push_back(char);

/* pop_back:
   removes the last element in strings character array
*/
char String::pop_back()
{
	char ret = characters[length-1];
	characters[length-1] = '\0';
	length -= 1;
	return ret;
}

// overloaded operator<<
std::ostream& operator<<(std::ostream& os, const String& str) { return os << str.characters; }

//overloaded operator>>
std::istream& operator>>(std::istream& is, String& str)
{
	char* arr = new char[255];
	is >> arr;
	str = arr;	
	return is;	
}

//swap
String& String::swap(String& str)
{
	String tmp = str;
	str = *this;
	*this = tmp;	
}
