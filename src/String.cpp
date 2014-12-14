#include <iostream>
#include <initializer_list>
#include "String.h"
#include "assert.h"

//default constructor
String::String()
	:length_{0}, characters{new char[length_ + 1]}
{
	characters[length_] = '\0';
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
	delete[] characters;
	length_ = 0;
}

//Return the amount of characters in a String
size_t String::size() const { return length_; }

/* Same as size(). Length and size "mean" the same thing,
but when we speak of strings we prefer the term length. 
Size is better with iterators.
*/
size_t String::length() const { return length_; }

/*
   strlen equivalent
   arg: const char* p
   counts char-arrays elements
   result: number of elements in given char-array
*/
size_t strlen(const char* p)
{
	size_t count = 0;
	while(*p) { ++count; ++p; }
	return count;
}

/*
   strcmp equivalent
   arg: char* ptr1, char* ptr2
   return value:
    <0: first character that does not match has a lower value in ptr1 than in ptr2
    0: the contents of both char arrays are equal
    >0: the first character that does not match has a greater value in ptr1 than in ptr2
*/
size_t strcmp(const char* ptr1, const char* ptr2)
{
	size_t res = 0;
	if(strlen(ptr1) == 0 && strlen(ptr2) == 0) return 0;
	if(strlen(ptr1) > strlen(ptr2)) return 1; //if prt1 is longer, then there is a comparison between some char and '\0'
	if(strlen(ptr1) < strlen(ptr2)) return -1; //if prt1 is longer, then there is a comparison between '\0' and some char 
	
	//if ptr1 and ptr2 have equal length
	for(size_t i = 0; i < strlen(ptr1); ++i) { 
	  if(ptr1[i] > ptr2[i]) { ++res; break; }
	  if(ptr1[i] < ptr2[i]) { --res; break; }
	}
	return res;
}

//copy assignment
String& String::operator=(const String& str)
{
	check();
	str.check();
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
	check();
	str.check();
	safe_release(characters);
	characters = str.characters;
	length_ = str.length();
	str.characters = nullptr;
	str.length_ = 0;
	return *this;	
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

// Erases all characters from String and sets the length as zero
void String::clear()
{
	*this = String(); // good bye world!
}

//returns a non-modifiable standart C character array version of the String
const char* String::c_str() const
{
	check();
	if(characters != nullptr)
		return characters;
	return nullptr;	
}

const String operator+(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	String str(lhs);
	return str += rhs;
}

const String& String::operator+=(const String& rhs)
{
	check();
	rhs.check();
	insert(length_, rhs);
	return *this;
}

/* Other functions require deletion of characters array.
   This function helps to do this task safely.
*/
inline void String::safe_release(char* chars)
{
	if(chars != nullptr) {
	  delete[] chars;
	  chars = nullptr;
	}	
}

//Overloaded logic operators
bool operator==(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return (strcmp(lhs.characters,rhs.characters) == 0);
}

bool operator!=(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return !(strcmp(lhs.characters, rhs.characters) == 0);
}

bool operator<(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return (strcmp(lhs.characters,rhs.characters) < 0);
}

bool operator<=(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return (strcmp(lhs.characters,rhs.characters) <= 0);
}

bool operator>(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return (strcmp(lhs.characters,rhs.characters) > 0);
}
bool operator>=(const String& lhs, const String& rhs)
{
	lhs.check();
	rhs.check();
	return (strcmp(lhs.characters,rhs.characters) >= 0);
}

//overloaded operator[]
char& String::operator[](size_t i)
{
	check();
	if( i < 0 || i > length_ )
		throw StringIndexOutOfBounds();
	return characters[i];
}

char String::operator[](size_t i) const
{
	check();
	if( i < 0 || i > length_ )
		throw StringIndexOutOfBounds();
	return characters[i];
}

//push_front
void String::push_front(const char& ch)
{
	check();
	insert(0, ch);
}

//push_back
void String::push_back(const char& ch)
{
	check();
	insert(length_, ch);
}

/* pop_back:
   removes the last element in strings character array
*/
char String::pop_back()
{
	check();//even empty string should have '\0'
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
void String::insert(size_t position, const char& ch)
{
	check();
	if(position < 0 || position > length_) throw StringIndexOutOfBounds();
	char* tmp = new char[length_];
	tmp = characters;

	characters = new char[length_ + 2];
	length_++;
	
	for(size_t i = 0; i < position; ++i) { characters[i] = tmp[i]; } //characters before position
	for(size_t i = position; i < length_; ++i) { characters[i] = tmp[i-1]; } //characters after position

	characters[position] = ch; //insertion
	characters[length_] = '\0'; //last character
	safe_release(tmp);
}

/* Inserts a String into String.
   Possible cases are the same as above.
*/
void String::insert(size_t position, const String& str)
{
	check();
	if(position < 0 || position > length_) throw StringIndexOutOfBounds();
	str.check();	
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
}

// erases a character from a single position
void String::erase(const size_t& position)
{
	check();
	if(position < 0 || position >= length_) throw StringIndexOutOfBounds();
	
	char* tmp = new char[length_+1];	
	tmp = characters;

	characters = new char[length_];
	for(size_t i = 0; i<position; ++i) { characters[i] = tmp[i]; }
	for(size_t i = position; i<length_; ++i) { characters[i] = tmp[i+1]; }	
	--length_;
	safe_release(tmp); // bye bye... :(
}

// Erases a substring from String. Substring is marked with constants begin and end which are indexes of String 
void String::erase(const size_t& begin, const size_t& end)
{
	check();
	//Sanity checks
	if(end < begin) throw StringIndexOutOfBounds();
	if(end < 0 || end >= length_) throw StringIndexOutOfBounds();
	if(begin < 0 || begin >= length_) throw StringIndexOutOfBounds();
	
	//if begin and end are same, we can use erase(const size_t&);	
	if(begin == end) { erase(end); }
	
	char* tmp = new char[length_+1];	
	tmp = characters;
	
	size_t delta = end - begin; // delta is the "size" of substr marked by constants begin and end
	++delta; //if end: 7, begin: 7 => delta: 1 (single character has size of one)

	length_ -= delta;
	characters = new char[length_+1];
	for(size_t i = 0; i<begin; ++i) { characters[i] = tmp[i]; }
	for(size_t i = begin; i<length_; ++i) { characters[i] = tmp[i+end]; }	
	
	safe_release(tmp); // bye bye... :(
}


// overloaded operator<<
std::ostream& operator<<(std::ostream& os, const String& str)
{
	str.check();
	return os << str.characters;
}

//overloaded operator>>
std::istream& operator>>(std::istream& is, String& str)
{
	str.check();
	char* arr = new char[String::MAX_LENGTH + 1];
	is >> arr;
	str = arr;	
	return is;	
}

//swaps contents of two strings
String& String::swap(String& str)
{
	check();
	str.check();
	String tmp = str;
	str = *this;
	*this = tmp;	
}

//
void String::check() const
{
	assert(length_ >= 0);
	if(length_ >= 0)
	  assert(characters[length_] == '\0');			
}
