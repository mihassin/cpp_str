#include <iostream>
#include <initializer_list>
#include "String.h"

//default constructor
String::String()
	:length_{0}, characters{new char[length_ + 1]}
{
	characters[1] = '\0';
}

//String from char array
String::String(const char* chars)
	:length_{strlen(chars)}, characters{new char[length_ + 1]}
{
	//coping the values
	for(size_t i = 0; i <= length_; ++i) { characters[i] = chars[i]; }

	//last character of string is the null char '\0'
	characters[length_] = '\0';
}

/* Copy constructor.
   Constructor structure is similar to String::String(const char* chars).
   Only difference is the function arg, which alters few lines.
*/
String::String(const String& str)
	:length_{str.length()}, characters{new char[length_ + 1]}
{
	for(size_t i = 0; i <= length_; ++i) { characters[i] = str[i]; }

	characters[length_] = '\0';
}

/*Constructor for initializer_list for argument {'H', 'e', 'l', 'l', 'o'}
	Inside curly brackets:
	1. copies lists first pointer
	2. uses for-loop to traverse Strings char array that has same amount of cells as list has elements
	   and copies the values from list to Strings char array.
	3. last value of string is a null char '\0'
*/
String::String(std::initializer_list<char> lst)
	:length_{lst.size()}, characters{new char[length_ + 1]}
{
	const char* p = lst.begin();
	for(size_t i = 0; i <= length_; ++i) { characters[i] = *p; ++p; }
	characters[length_] = '\0';
}

//Move constructor
String::String(String&& str)
	:length_{str.length()}, characters{str.characters}
{
	str.length_ = 0;
	str.characters = nullptr;
}

//Destructor
String::~String()
{
	if(characters != NULL) {
	  delete[] characters;
	  characters = NULL;
	}
}

//copy assignment
String& String::operator=(const String& str)
{
	if(this==&str) return *this;
	
	length_ = str.length();
	char* arr = new char[length_ + 1];		
	for(size_t i = 0; i <= length_; ++i) { arr[i] = str[i]; }
	arr[length_] = '\0';
	safe_release(characters);
	characters = arr;
	return *this;
}

//move assignment
String& String::operator=(String&& str)
{
	safe_release(characters);
	characters = str.characters;
	length_ = str.length();
	str.characters = nullptr;
	str.length_ = 0;
	return *this;	
}

/*
   strlen equivalent
   arg: const char* p
   counts char-arrays elements
   result: number of elements in given char-array
*/
size_t String::strlen(const char* p)
{
	size_t count = 0;
	while(*p) { ++count; ++p; }
	return count;
}

//overloaded operator[]
char& String::operator[](size_t i)
{
	if( i < 0 || i > length_ )
		throw StringIndexOutOfBounds();
	return characters[i];
}

char String::operator[](size_t i) const
{
	if( i < 0 || i > length_ )
		throw StringIndexOutOfBounds();
	return characters[i];
}

//push_back
void String::push_back(const char& ch)
{
	insert(length_, ch);
}

/* pop_back:
   removes the last element in strings character array
*/
char String::pop_back()
{
	if(this->empty()) return '\0';

	char popped_char = characters[length_ - 1];
	characters[length_ - 1] = '\0';
	length_ -= 1;
	return popped_char;
}

/* Insertion of a single character
   Possible cases:
	A. Infront of the String
	B. In the middle of the String, 
	   where position marks the character which infront the new character will be placed
	C. To the end of the String
*/
bool String::insert(size_t position, const char& ch)
{
	if(position < 0 || position > length_) return false;
	char* tmp = new char[length_];
	tmp = characters;

	characters = new char[length_ + 2];
	length_++;
	
	for(size_t i = 0; i < position; ++i) { characters[i] = tmp[i]; } //characters before position
	for(size_t i = position; i < length_; ++i) { characters[i] = tmp[i-1]; } //characters after position

	characters[position] = ch; //insertion
	characters[length_] = '\0'; //last character
	safe_release(tmp);
	return true;
}

/* Inserts a String into String.
   Possible cases are the same as above.
*/
bool String::insert(size_t position, const String& str)
{
	if(position < 0 || position > length_) return false;
	char* tmp = new char[length_];
	tmp = characters;
	
	const size_t s_len = str.length();
	
	characters = new char[length_ + s_len + 1];
	length_ += s_len;
	
	for(size_t i = 0; i < position; ++i) { characters[i] = tmp[i]; } //characters before position
	for(size_t i = position+s_len; i < length_; ++i) { characters[i] = tmp[i-s_len]; } //characters after position
	
	size_t j = 0;
	for(size_t i = position; i < position+s_len; ++i) { characters[i] = str[j]; ++j; }  	
	characters[length_] = '\0'; //last character
	safe_release(tmp);	
	return true;
}

//erase
bool String::erase(const size_t& position)
{
	if(position < 0 || position >= length_) return false;
	
	char* tmp = new char[length_+1];	
	tmp = characters;

	characters = new char[length_];
	for(size_t i = 0; i<position; ++i) { characters[i] = tmp[i]; }
	for(size_t i = position; i<length_; ++i) { characters[i] = tmp[i+1]; }	
	--length_;
	safe_release(tmp); // bye bye... :(
	return true;
}

bool String::erase(const size_t& begin, const size_t& end)
{
	//Sanity checks
	if(end < begin) return false;
	if(end < 0 || end >= length_) return false;
	if(begin < 0 || begin >= length_) return false;
	
	//if begin and end are same, we can use erase(const size_t&);	
	if(begin == end) { erase(end); return true; }
	
	char* tmp = new char[length_+1];	
	tmp = characters;
	
	size_t delta = end - begin; // delta is the "size" of substr marked by constants begin and end
	++delta; //if end: 7, begin: 7 => delta: 1

	length_ -= delta;
	characters = new char[length_+1];
	for(size_t i = 0; i<begin; ++i) { characters[i] = tmp[i]; }
	for(size_t i = begin; i<length_; ++i) { characters[i] = tmp[i+end]; }	
	
	safe_release(tmp); // bye bye... :(
	return true;
}


// overloaded operator<<
std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.characters;
}

//overloaded operator>>
std::istream& operator>>(std::istream& is, String& str)
{
	char* arr = new char[String::MAX_LENGTH + 1];
	is >> arr;
	str = arr;	
	return is;	
}

//swaps contents of two strings
String& String::swap(String& str)
{
	String tmp = str;
	str = *this;
	*this = tmp;	
}

/* Checks if String has characters.
   If String is empty, empty() returns true.
   Else empty() returns false.
*/
bool String::empty()
{
	if(length_ == 0) return true;
	else return false;
}

/* Other functions require deletion of characters array.
   This function helps to do this task safely.
*/
inline void String::safe_release(char* chars)
{
	if(chars != NULL) {
	  delete[] chars;
	  chars = NULL;
	}	
}
