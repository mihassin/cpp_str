#ifndef STRING_H
#define STRING_H

 class String
 {
    public:
	  // Constructors
	  String();	
	  String(const char*);
	  String(const String&);

	  //Destructor
	  ~String();

	  //copy assignment
	  String& operator=(const String&);
	
	  //Returns String length
	  unsigned int get_length() const { return length; }

	  //required functions

          //overloaded operator[] !cases i > length
	  char& operator[](int i) { return characters[i]; }
	  char operator[](int i) const { return characters[i]; }

	  //insertion and deletion functions
	  void push_back(char);
	  void pop_back();
	  void insert();
	  void erase();
	
	  //overloaded input and output operations
	  friend std::ostream& operator<<(std::ostream&, const String&);
	  friend std::istream& operator>>(std::istream&, String&);

	  //swap() exhanges the contents of two strings
  	  String& swap(const String&);
  private:
	  unsigned int length;
	  char* characters;
};

#endif
