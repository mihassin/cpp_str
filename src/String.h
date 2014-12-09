class String
{
  public:
	  // Constructors
	  String();	
	  String(char*);
	  String(const String&);

	  //Destructor
	  ~String();

	  //copy assignment
	  String& operator=(const String&);
	
	  //Returns String length
	  unsigned int const get_length() { return length; }
	
	  //required functions

    //overloaded operator[]
	  char& operator[](unsigned int);	

	  //insertion and deletion functions
	  void push_back(char);
	  void pop_back();
	  void insert();
	  void erase();
	
	  //swap() exhanges the contents of two strings
  	String& swap(const String&);
  private:
	  unsigned int length;
	  char* characters;
};

//overloaded input and output operations
std::ostream& operator<<(std::ostream&, const String&);
std::istream& operator>>(std::istream&, String&);
