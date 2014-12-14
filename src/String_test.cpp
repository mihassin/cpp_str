#include <iostream>
#include "String.h"
#include "assert.h"

using namespace std;

// type conversions 
// Required: const char* -> String
void f(String s) 
{
 //...
}

template <typename T>
bool assert_equals(T result, T expected)
{
	try{
		assert(result == expected);
	} catch(StringException) {
		throw StringException();
	}
	return true;
}

//1.
bool test_default_ctor()
{
	String str;
	size_t zero = 0;
	try{
		assert_equals(str.size(), zero);
	} catch(StringException) {
		cout << "test_default_ctor fail: String should be empty and have length 0\n"; 	
		return false;	
	}
	return true;
}

//2.
bool test_char_array_ctor()
{
	String str = "hello world!";
	size_t twelve = 12;
	try{
		assert(strcmp(str.c_str(), "hello world!") == 0); //function strcmp defined in String.cpp
		assert_equals(str.length(), twelve);
	} catch(StringException) {
		cout << "test_char_array_ctor fail: String should be \"hello world\" and it's length should be 12\n";
		return false;	
	}
	return true;
}

//3.
bool test_str_ref_ctor()
{
	String str1 = "String";
	String str2 = str1;
	size_t original_length = str1.length();
	try{
		assert_equals(str2.length(), original_length);
		assert(str1.size() == str2.length()); // length is still same eventhough we use different functions
		assert((strcmp(str1.c_str(), str2.c_str())) == 0);
	} catch(StringException) {
		cout << "test_str_ref_ctor fail: str2 should have same length and characters as str1\n";
		return false;	
	}
	return true;
}

//4.
bool test_initializer_list_ctor()
{
	String str = {'H','e','l','l','o'};
	size_t five = 5;
	String hello = "Hello";
	try{
		assert_equals(str.length(), five);
		assert(strcmp(str.c_str(), hello.c_str()) == 0);
	} catch(StringException) {
		cout << "test_initializer_list_ctor fail: When String is given a initializer list as an argument,\n";
		cout << "                       it should be same as String which is constructed with const char*";
		return false;	
	}
	return true;
}

int test_constructors()
{
	int passed = 0;
	if(test_default_ctor())++passed;
	if(test_char_array_ctor())++passed;
	if(test_str_ref_ctor())++passed;
	if(test_initializer_list_ctor())++passed;	
	return passed;
}

int main()
{
	int passed = 0;
	const int total = 20;
	String status = "FAILURE!";

	passed += test_constructors();

	if(passed==total) status = "Success!";
	cout << "---------------------------\n";
	cout << "| String class unit-tests |\n";
	cout << "| Status: " << status << "        |\n";
	cout << "| Results:                |\n";
	cout << "| " << passed << " / " << total << " passed.          |\n";
	cout << "---------------------------\n";  

	return 0;
}
