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
	  String(String&&);
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
		bool operator!=(const const_iterator& b) const { return !(p_ == b.p_); } 
	    private:
		T* p_;
	  };

	  //iterator functions
	  iterator<char> begin() { return characters; }
	  iterator<char> end() { return characters + length_; }

	  const_iterator<char> begin() const { return characters; } 
	  const_iterator<char> end() const { return characters + length_; }

	  //Return the amount of characters in a String
	  size_t size() const { return length_; }

	  //copy assignment
	  String& operator=(const String&);
	  //move assignment
	  String& operator=(String&&);
	
	  /* Same as size(). Length and size "mean" the same thing,
	     but when we speak of strings we prefer the term length. 
	     Size is better with iterators.
	  */
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
	  void push_back(const char&);
	  char pop_back();
	  void insert(size_t, const char&);
	  void insert(size_t, const String&);
	  bool erase(const size_t);
	
	  //overloaded input and output operations
	  friend std::ostream& operator<<(std::ostream&, const String&);
	  friend std::istream& operator>>(std::istream&, String&);


	  //swap() exhanges the contents of two strings
  	  String& swap(String&);

	  //checks if String has characters
	  bool empty();

	  /* Some functions require characters array deletion.
	     This function will do it safely.
	  */
	  inline void safe_release(char*);
	private:
	  size_t length_;
	  char* characters;
};

#endif
