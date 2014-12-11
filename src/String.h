#ifndef STRING_H
#define STRING_H

 class String
 {
    public:
	  // Constructors
	  String();	
	  String(const char*);
	  String(const String&);
	  String(String&&); //move c:tor
	  //String(initializer_list<char> lst);

	  //Destructor
	  ~String() { delete[] characters; }

	  //copy assignment
	  String& operator=(const String&);
	  //move assignment
	  String& operator=(String&&);
	
	  //Returns String length
	  unsigned int get_length() const { return length; }

	  // C string.h equivalent function. Returns the number of cells in char array
	  int strlen(const char*);

	  //required functions

          //overloaded operator[] !cases i > length
	  char& operator[](int i) { return characters[i]; }
	  char operator[](int i) const { return characters[i]; }

	  //insertion and deletion functions
	  void push_back(char);
	  char pop_back();
	  void insert();
	  void erase();
	
	  //overloaded input and output operations
	  friend std::ostream& operator<<(std::ostream&, const String&);
	  friend std::istream& operator>>(std::istream&, String&);

	  //swap() exhanges the contents of two strings
  	  String& swap(String&);
  private:
	  unsigned int length;
	  char* characters;
};

#endif
