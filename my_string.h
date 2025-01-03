#ifndef _MYSTRING_H_
#define _MYSTRING_H_

class MyString
{
private:
	size_t string_current_size_; // current size of "Hello" = 5 char symbols
	size_t string_capacity_; // capacity of "Hello" 5 char symbols + 1 = 6
	char* string_address_; //address in memory


public:
	MyString(); // default constructor initialization
	MyString(const char* string, size_t count); //costructor for string with count declaration
	MyString(const char* string); // constructor for string without count declaration
	MyString(size_t count, char symbol); // constructor for string of count * "symbol" symbols
	MyString(const std::string& std_string); // constructor for std::string
	MyString(const MyString& source); // constructor to create a copy of MyString object
	~MyString(); // destructor clears memory to prevent memory leaks

	char* c_str(); // return string_address_ that ends with '\0'
	char* data() const; // return string_address_
	bool empty() const; // if string is empty return true, else false
	size_t capacity() const; // return string_capacity_
	size_t length() const; // return size()
	size_t size() const; // return string_current_size_
	size_t count_size(const char* string) const; // helper that counts size if it is not directly set by user
	void shrink_to_fit(); // compresses string to its real size
	void erase(int index, int count); // erases count symbols from string index
	void clear(); // erases all symbols erase(0, string_current_size_)

	void insert(int index, int count, char symbol); // insert in string[index] count symbols 'symbol'
	void insert(int index, const char* string); // insert in string[index] char array
	void insert(int index, const char* string, int count); //insert in string[index] count symbols of char array
	void insert(int index, const std::string& std_string); // insert in std::string[index] char array
	void insert(int index, const std::string& std_string, int count); // insert in std::string[index] count symbols of char array
	void append(int count, char symbol);
	void append(const char* string);
	void append(const char* string, int index, int count);
	void append(const std::string& std_string);
	void append(const std::string& std_string, int index, int count);
	void replace(int index, int count, const char* string);
	void replace(int index, int count, const std::string& std_string);
	MyString substr(int index) const;
	MyString substr(int index, int count) const;
	int find(const char* string) const;
	int find(const char* string, int start_index) const;
	int find(const std::string& std_string) const;
	int find(const std::string& std_string, int start_index) const;

	MyString operator+(const MyString& other) const; // Operator +(Mystring)
	MyString operator+(const char* string) const; // Operator +(“char string”)
	MyString operator+(const std::string& std_string) const; // Operator +(std::string)
	MyString& operator+=(const char* string); // Operator +=(“char string”)
	MyString& operator+=(const std::string& std_string); // Operator +=(std::string)
	MyString& operator+=(const MyString& string); // Operator +=(MyString::string)
	MyString& operator=(const char* string); // Operator=(“char string”)
	MyString& operator=(const std::string& std_string); // Operator=(std::string)
	MyString& operator=(char symbol); // Operator=(‘char’)
	MyString& operator=(const MyString& other); // Operator=(MyString)

	// Operator [] for writing symbols
	char& operator[](size_t index);

	// Operator [] for reading symbols
	const char& operator[](size_t index) const;
	bool operator==(const MyString& other) const; // Operator==()
	bool operator!=(const MyString& other) const; // Operator!=()
	bool operator<(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>=(const MyString& other) const;

	// friend operators for I/O
	friend std::ostream& operator<<(std::ostream& os, const MyString& myStr);
	friend std::istream& operator>>(std::istream& is, MyString& myStr);

};

#endif // _MYSTRING_H_

