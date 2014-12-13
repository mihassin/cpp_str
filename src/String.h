#ifndef STRING_H
#define STRING_H

class StringIndexOutOfBounds{};

class String
{
	public:
	  using size_t = unsigned long;

	  // Constructors
	  String();	
	  String(const char*);
	  String(const String&);
	  String(String&&); //move c:tor
	  String(std::initializer_list<char>);

	  //Destructor
	  ~String();

	  // Iterators
	  template<typename T>
	  class iterator
	  {
	    public:
		iterator(T* p) : p_{p} {}
		
		iterator& operator++() { ++p_; return *this; }
		iterator& operator--() { --p_; return *this; }
		
		T& operator*() { return *p_; }
		T* operator->() { return p_; }
		
		bool operator==(const iterator& b) const { return p_ == b.p_; }
		bool operator!=(const iterator& b) const { return p_ != b.p_; } 
	    private:
		T* p_;
	  };
	  
	  template<typename T>
	  class const_iterator
	  {
	    public:
		const_iterator(T* p) : p_{p} {}
		
		const_iterator& operator++() { ++p_; return *this; }
		const_iterator& operator--() { --p_; return *this; }
		
		T& operator*() { return *p_; }
		T* operator->() { return p_; }
		
		bool operator==(const const_iterator& b) const { return p_ == b.p_; }
		bool operator!=(const const_iterator& b) const { return p_ != b.p_; } 
	    private:
		T* p_;
	  };

	  iterator<char> begin();
	  iterator<char> end();

	  const_iterator<char> begin() const;
	  const_iterator<char> end() const;

	  size_t size();

	  //copy assignment
	  String& operator=(const String&);
	  //move assignment
	  String& operator=(String&&);
	
	  //Returns String length
	  size_t length() const { return length_; }

	  //C string.h equivalent function. Returns the number of cells in char array
	  size_t strlen(const char*);

	  //Maximum length for String object (amount of characters in one String)
	  enum { MAX_LENGTH = 4096 };

	  //required functions

          //overloaded operator[] !cases i > length
	  char& operator[](size_t);
	  char operator[](size_t) const;

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

	  //checks if String has characters
	  bool empty();	
	private:
	  size_t length_;
	  char* characters;
};

#endif
