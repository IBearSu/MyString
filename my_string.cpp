#include <iostream>
#include <string>
#include "my_string.h"

/*--------------------------------------------------------------------------Operators--------------------------------------------------------------------------*/
MyString MyString::operator+(const MyString& other) const // Operator +(Mystring)
{
	MyString result(*this);
	result.insert(result.string_current_size_, other.string_address_);
	return result;
}

MyString MyString::operator+(const char* string) const // Operator +(“char string”)
{
	MyString result(*this);
	result.insert(result.string_current_size_, string);
	return result;
}

MyString MyString::operator+(const std::string& std_string) const // Operator +(std::string)
{
	MyString result(*this);
	result.insert(result.string_current_size_, std_string.c_str());
	return result;
}

MyString& MyString::operator+=(const char* string) 
{
	this->insert(this->string_current_size_, string);
	return *this;
}

MyString& MyString::operator+=(const std::string& std_string) //Operator +=(“char string”)
{
	this->insert(this->string_current_size_, std_string.c_str());
	return *this;
}

MyString& MyString::operator+=(const MyString& string) //Operator +=(“char string”)
{
	this->insert(this->string_current_size_, string.string_address_);
	return *this;
}

MyString& MyString::operator=(const char* string) 
{
	this->clear(); 
	this->insert(0, string);
	return *this;
}


MyString& MyString::operator=(const MyString& other) 
{
	if (this != &other) {
		this->clear();
		this->insert(0, other.string_address_);
	}
	return *this;
}



MyString& MyString::operator=(const std::string& std_string) 
{
	this->clear(); 
	this->insert(0, std_string.c_str()); 
	return *this;
}


MyString& MyString::operator=(char symbol) 
{
	this->clear(); 
	this->append(1, symbol);
	return *this;
}


// unconst version for writing symbols
char& MyString::operator[](size_t index) 
{
	if (index >= string_current_size_) 
	{
		throw std::out_of_range("Index out of range");
	}
	return string_address_[index];
}

// const version for reading symbols
const char& MyString::operator[](size_t index) const 
{
	if (index >= string_current_size_) 
	{
		throw std::out_of_range("Index out of range");
	}
	return string_address_[index];
}


bool MyString::operator==(const MyString& other) const // Operator==()
{
	if (string_current_size_ != other.string_current_size_) {
		return false;
	}
	return std::memcmp(string_address_, other.string_address_, string_current_size_) == 0;
}

bool MyString::operator!=(const MyString& other) const // Operator!=()
{ 
	return !(*this == other);  // delegating to Operator==()
}

bool MyString::operator<(const MyString& other) const 
{
	size_t min_size = std::min(string_current_size_, other.string_current_size_);
	int result = std::memcmp(string_address_, other.string_address_, min_size);
	if (result < 0) {
		return true;  // First string is less
	}
	else if (result > 0) {
		return false;  // First string is bigger
	}

	return string_current_size_ < other.string_current_size_;
}

bool MyString::operator>(const MyString& other) const 
{
	return other < *this;  // Delegation to operator<
}

bool MyString::operator<=(const MyString& other) const 
{
	return !(*this > other);  // Delegation to operator>
}

bool MyString::operator>=(const MyString& other) const 
{
	return !(*this < other);  // Delegation to operator<
}

std::ostream& operator<<(std::ostream& os, const MyString& myStr) 
{
	os << myStr.data();
	return os;  
}

std::istream& operator>>(std::istream& is, MyString& myStr)
{

	// Skip leading space
	is >> std::ws;
	// Initial buffer size
	constexpr size_t buffer_size = 1024;
	char buffer[buffer_size];
	size_t length = 0;
	char ch;
	// Read characters until a space, newline, or end of stream is encountered
	while (is.get(ch) && !std::isspace(ch))
	{
		// Filling up temporary buffer
		buffer[length++] = ch;

		// If buffer is full, add its containment to object string and set length to zero 
		if (length == buffer_size)
		{
			myStr.insert(myStr.size(), buffer, length);
			length = 0;
		}
	}

	// adding remaining symbols to string
	if (length > 0)
	{
		myStr.insert(myStr.size(), buffer, length);
	}

	return is;
}




/*--------------------------------------------------------------------------Operators--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------Functional methods--------------------------------------------------------------------------*/

/*
starting with C++11 and futrther c_str() and data() are equivalents, 
it menans string is always returned ending with '\0':
	_NODISCARD _CONSTEXPR20 _Ret_z_ const _Elem* c_str() const noexcept {
		return _Mypair._Myval2._Myptr();
	}

	_NODISCARD _CONSTEXPR20 _Ret_z_ const _Elem* data() const noexcept {
		return _Mypair._Myval2._Myptr();
	}
*/
char* MyString::c_str()                     
{
	string_address_[string_current_size_] = '\0';
	return string_address_;
}

char* MyString::data() const
{
	return string_address_;
}

size_t MyString::length() const
{
	return size(); // delegation
}

size_t MyString::size() const
{
	return string_current_size_;
}

bool MyString::empty() const
{
	if (string_current_size_ == 0 && string_address_[string_current_size_] == '\0')
	{
		return true;
	}
	return false;
}

size_t MyString::capacity() const
{
	return string_capacity_;
}

void MyString::shrink_to_fit()
{
	if (string_capacity_ - string_current_size_ > 1)
	{
		char* new_string = new char[string_current_size_ + 1];
		std::memcpy(new_string, string_address_, string_current_size_);
		new_string[string_current_size_] = '\0';
		delete[] string_address_;
		string_address_ = new_string;
		string_capacity_ = string_current_size_ + 1;
	}
}

void MyString::erase(int index, int count) {
	if (index < 0 || index >= string_current_size_ || count < 0 || index + count > string_current_size_) {
		throw std::out_of_range("Index or count is out of range");
	}
	std::memmove(string_address_ + index, string_address_ + index + count, string_current_size_ - index - count);
	string_current_size_ -= count;
	string_address_[string_current_size_] = '\0';
}

//              /\
//delegated to  ||
//              ||
void MyString::clear()
{
	erase(0, string_current_size_);  // delegation to erase
}

void MyString::insert(int index, int count, char symbol)
{
	char* new_char = new char[count + 1];
	std::memset(new_char, symbol, count);
	new_char[count] = '\0';
	insert(index, new_char, count); //partly delegated to || insert(int index, const char* string, int count)
	delete[] new_char;              //                    ||
}                                   //                    \/



void MyString::insert(int index, const char* string)
{
	insert(index, string, count_size(string));
}
//              ||
//delegated to  ||
//              \/
void MyString::insert(int index, const char* string, int count) {
	if (index < 0 || index > string_current_size_) {
		throw std::out_of_range("Index or count is out of range");
	}

	size_t required_capacity = string_current_size_ + count + 1;
	if (required_capacity > string_capacity_) {
		string_capacity_ = required_capacity;
		char* new_string = new char[string_capacity_];
		std::memcpy(new_string, string_address_, index);
		std::memcpy(new_string + index, string, count);
		std::memcpy(new_string + index + count, string_address_ + index, string_current_size_ - index);
		delete[] string_address_;
		string_address_ = new_string;
	}
	else {
		std::memmove(string_address_ + index + count, string_address_ + index, string_current_size_ - index);
		std::memcpy(string_address_ + index, string, count);
	}

	string_current_size_ += count;
	string_address_[string_current_size_] = '\0';
}

//              /\
//delegated to  ||
//              ||
void MyString::insert(int index, const std::string& std_string)
{
	insert(index, std_string.c_str(), std_string.size());
}
//delegated to  ||
void MyString::insert(int index, const std::string& std_string, int count)
{
	insert(index, std_string.c_str(), count);
}

void MyString::append(int count, char symbol) 
{
	insert(string_current_size_, count, symbol);
}

void MyString::append(const char* string) 
{
	insert(string_current_size_, string);
}

void MyString::append(const char* string, int index, int count) 
{
	if (index >= 0 && index + count <= std::strlen(string)) 
	{
		insert(string_current_size_, string + index, count);
	}
	else 
	{
		throw std::out_of_range("Index or count is out of range");
	}
}

void MyString::append(const std::string& std_string) 
{
	insert(string_current_size_, std_string.c_str());
}

void MyString::append(const std::string& std_string, int index, int count) 
{
	if (index >= 0 && index + count <= std_string.size()) 
	{
		insert(string_current_size_, std_string.c_str() + index, count);
	}
	else 
	{
		throw std::out_of_range("Index or count is out of range");
	}
}

void MyString::replace(int index, int count, const char* string) 
{
	if (index < 0 || index >= string_current_size_ || index + count > string_current_size_) 
	{
		throw std::out_of_range("Index or count is out of range");
		return;
	}
	erase(index, count);
	insert(index, string);
}

void MyString::replace(int index, int count, const std::string& std_string) 
{
	replace(index, count, std_string.c_str());
}

MyString MyString::substr(int index) const 
{
	if (index < 0 || index >= string_current_size_) 
	{
		throw std::out_of_range("Index or count is out of range");
		return MyString();
	}
	return MyString(string_address_ + index);
}

MyString MyString::substr(int index, int count) const 
{
	if (index < 0 || index >= string_current_size_ || count < 0 || index + count > string_current_size_) {
		throw std::out_of_range("Index or count is out of range");
		return MyString();
	}

	return MyString(string_address_ + index, count);
}

int MyString::find(const char* string) const 
{
	return find(string, 0);  // Delegation
}

int MyString::find(const char* string, int start_index) const 
{
	if (start_index < 0 || start_index >= string_current_size_) 
	{
		std::cerr << "MyString::find: start_index out of range" << std::endl;
		return -1;
	}

	size_t string_length = count_size(string);
	if (string_length == 0) 
	{
		return -1; 
	}

	for (int i = start_index; i <= string_current_size_ - string_length; ++i) 
	{
		if (std::memcmp(string_address_ + i, string, string_length) == 0) 
		{
			return i;
		}
	}
	return -1;
}

int MyString::find(const std::string& std_string) const 
{
	return find(std_string.c_str(), 0);  // Delegation
}

int MyString::find(const std::string& std_string, int start_index) const 
{
	return find(std_string.c_str(), start_index);  // Delegation
}




/*--------------------------------------------------------------------------Functional methods--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------Constructors--------------------------------------------------------------------------*/
MyString::MyString(const std::string& std_string) :MyString(std_string.c_str()) {}; // Constructor(std::string)
//              ||
//delegated to  ||
//              \/
MyString::MyString(const char* string) :MyString(string, count_size(string)) {}; // Constructor(“char string”) for char array
//              ||
//delegated to  ||
//              \/
MyString::MyString(const char* string, size_t count) // Constructor(“char string”, count)
{
	string_current_size_ = count;
	string_capacity_ = count + 1;
	string_address_ = new char[string_capacity_];
	std::memcpy(string_address_, string, count);
	string_address_[count] = '\0';
}
//              /\
//delegated to  ||
//              ||
MyString::MyString() :MyString("", 0) {} // default Constructor() description
//delegated to  ||
MyString::MyString(const MyString& source) :MyString(source.string_address_, source.string_current_size_) {};

MyString::MyString(size_t count, char symbol) // Constructor(count, char)
{
	string_current_size_ = count;
	string_capacity_ = count + 1;
	string_address_ = new char[string_capacity_];
	std::memset(string_address_, symbol, count);
	string_address_[count] = '\0';
};

size_t MyString::count_size(const char* string) const // helper that counts size if it is not directly set by user
{
	size_t size = 0;
	while (string[size] != '\0')
	{
		++size;
	}
	return size;
}

MyString::~MyString() // destructor
{
	if (string_address_ != nullptr) {
		delete[] string_address_;
		string_address_ = nullptr;
	}
	string_current_size_ = 0;
	string_capacity_ = 0;
}


/*--------------------------------------------------------------------------Constructors--------------------------------------------------------------------------*/

