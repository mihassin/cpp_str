#include <sstream>
#include <iostream>
#include "String.h"
#include "assert.h"

using namespace std;

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

bool assert_Strings(String& result, String expected)
{
	try{
		assert(result.length() == expected.length());
		assert(strcmp(result.c_str(), expected.c_str()) == 0); //function strcmp defined in String.cpp
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
		assert_Strings(str, "");
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
		assert_Strings(str, "hello world!");
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
		assert_equals(str1.size(), str2.length()); // length is still same eventhough we use different functions
		assert_Strings(str1, str2);
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
		assert_Strings(str, hello);
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

//5.
bool test_assignment()
{
	String str;
	String str1 = "hello";
	str1 = str; //both are now empty
	try{
		assert_Strings(str1, str);
		assert_Strings(str1, "");
		assert_equals(str1.empty(), true);
	} catch(StringException) {
		cout << "test_assignment fail: Strings aren't same after assignment.\n";
		return false;	
	}
	return true;
}

//6.
bool test_square_brackets_operator()
{
	String str = "hello";
	try{
		assert_equals(str[0], 'h');
		assert_equals(str[4], 'o');
	} catch(StringException) {
		cout << "test_square_brackets_operator() fail: Access to String through square brackets is faulty.\n";
		return false;	
	}
	return true;
}

//7.
bool test_square_brackets_operator_and_iterators()
{
	String str = "hello";
	size_t i = 0;
	try{
		for (auto it = str.begin();it != str.end();++it) {
			assert_equals(*it, str[i]); ++i;
		}
	} catch(StringException) {
		cout << "test_square_brackets_operator_and_iterators() fail: Access to String through square brackets is faulty or iterators are faulty.\n";
		return false;	
	}
	return true;
}

//8.
bool test_negative_index()
{
	String str;
	try{
		str[-999];
	} catch(StringIndexOutOfBounds) {
		return true;	
	}
	cout << "test_negative_index() fail: Strings don't have access to negative indexes\n";
	return false;
}

//9.
bool test_index_greater_than_length()
{
	String str;
	try{
		str[1];
	} catch(StringIndexOutOfBounds) {
		return true;	
	}
	cout << "test_index_greater_than_length() fail: Strings don't have access to beyond its length\n";
	return false;
}

int test_assigning_and_accessing()
{
	int passed = 0;
	if(test_assignment()) ++passed;
	if(test_square_brackets_operator()) ++passed;
	if(test_square_brackets_operator_and_iterators()) ++passed;
	if(test_negative_index()) ++passed;
	if(test_index_greater_than_length()) ++passed;	
	return passed;
}

//10.
bool test_push_back()
{
	String str;
	str.push_back('a');
	try{
		assert_equals(str[str.size()-1], 'a');
		assert_Strings(str, "a");
		assert_equals(str.length(), (size_t)1);
	} catch(StringException) {
		cout << "test_push_back() fail: push_back() should increase String length by one and add a desired character as a final character of the String.\n";
		return false;
	}
	return true;
}

//11.
bool test_pop_back()
{
	String str = "a";
	char a = str.pop_back();
	try{
		assert_equals(str.length(), (size_t)0);
		assert_equals(a, 'a');
		assert_Strings(str, "");
	} catch(StringException) {
		cout << "test_pop_back() fail: pop_back() should decrease String length by one and erase last character.\n";
		return false;
	}
	return true;
}

//12.
bool test_insert_character()
{
	String str;
	str.insert(0,'a');
	try{
		assert_equals(str[0], 'a');
		assert_Strings(str, "a");
		assert_equals(str.length(), (size_t)1);
	} catch(StringException) {
		cout << "test_insert_character() fail: insertion should add given character to given position.\n";
		return false;	
	}
	return true;
}

//13.
bool test_insert_String()
{
	String xx = "xx";
	xx.insert(1, "INSERTION");
	String correct = "xINSERTIONx";
	try{
		assert_Strings(xx, correct);
		assert_equals(xx.length(), correct.length());
	} catch(StringException) {
		cout << "test_insert_String() fail: inserting String inside another String isn't correct.\n";
		return false;	
	}
	return true;
}

//14.
bool test_erase_character()
{
	String str = "asd";
	str.erase(0);
	try{
		assert_Strings(str, "sd");
		assert_equals(str.length(), (size_t)2);
	} catch(StringException) {
		cout << "test_erase_character() fail: only the character in a given position should be erased\n";
		return false;	
	}
	return true;
}

//15.
bool test_erase_multiple_characters()
{
	String xx = "xERASEMEx";
	String erase = "ERASEME";
	String correct = "xx";
	
	size_t first = 1;
	size_t end = erase.length();
	
	xx.erase(first, end);	
	try{
		assert_Strings(xx, correct);
		assert_equals(xx.length(), correct.length());
	} catch(StringException) {
		cout << "test_erase_multiple_characters() fail: Multiple character erase doesn't work correctly\n";
		return false;	
	}
	return true;
}

//16.
bool test_erase_middle()
{
	String str = "corrXect";
	str.erase(4);
	String correct = "correct";
	try{
		assert_equals(str.length(), correct.length());
		assert_Strings(str, correct);
	} catch(StringException) {
		cout << "test_erase_middle() fail: erasing in the middle of String should only remove the character in the given position\n";
		return false;
	}
	return true;
}

//17.
bool test_push_front()
{
	String str = "-factor";
	size_t correct_len = str.length() + 1;
	str.push_front('X');
	try{
		assert_equals(str.length(), correct_len);
		assert_Strings(str, "X-factor");
	} catch(StringException) {
		cout << "test_push_front() fail: push_front() should add given character infront of String and increase the length by one\n";
		return false;
	}
	return true;
}

int test_insertions_and_deletions()
{
	int passed = 0;
	if(test_push_back()) ++passed;
	if(test_pop_back()) ++passed;
	if(test_insert_character()) ++passed;
	if(test_insert_String) ++passed;
	if(test_erase_character()) ++passed;
	if(test_erase_multiple_characters()) ++passed;
	if(test_erase_middle()) ++passed;
	if(test_push_front()) ++passed;
	return passed;
}

//18.
bool test_swap()
{
	String str1 = "hello";
	String str2 = "world";
	String before_swap1 = str1;
	String before_swap2 = str2;
	str1.swap(str2);
	try{
		assert_equals(str1.length(), before_swap2.length());
		assert_Strings(str1, before_swap2);
		assert_equals(str2.length(), before_swap1.length());
		assert_Strings(str2, before_swap1);
	} catch(StringException) {
		cout << "test_swap() fail: swap() should change the values of this and argument\n";
		return false;	
	}
	return true;
}

//19.
bool test_input()
{
	stringstream is("brown fox");
	String str;	
	try{
		is >> str;
		assert_Strings(str, "brown");
		is >> str;
		assert_Strings(str, "fox");
	} catch(StringException) {
		cout << "test_input() fail: input doesn't work correctly\n";
		return false;
	}
	return true;
}

//20.
bool test_output()
{
	stringstream os;
	String expected = "brown fox";
	os << expected;
	try{
		String str = os.str().c_str();
		assert_Strings(str, "brown fox");
	} catch(StringException) {
		cout << "test_output() fail: output doesn't work correctly\n";
		return false;
	}
	return true;
}

int test_io_and_swap()
{
	int passed = 0;
	if(test_swap()) ++passed;
	if(test_input()) ++passed;
	if(test_output()) ++passed;
	return passed;
}

int main()
{
	int passed = 0;
	const int total = 20;
	String status = "FAILURE!";

	passed += test_constructors();
	passed += test_assigning_and_accessing();
	passed += test_insertions_and_deletions();
	passed += test_io_and_swap();

	if(passed==total) status = "Success!";
	cout << "---------------------------\n";
	cout << "| String class unit-tests |\n";
	cout << "| Status: " << status << "        |\n";
	cout << "| Results:                |\n";
	cout << "| " << passed << " / " << total << " passed.         |\n";
	cout << "---------------------------\n";  

	return 0;
}
