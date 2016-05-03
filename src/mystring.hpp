#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

class StringValue{
	char *strData;
	size_t *ref_count;
public:
	StringValue();
	StringValue(char const* string);
	StringValue(StringValue const& newref);
	
	StringValue& operator=(StringValue const& rhs);
	
	~StringValue();
	
	size_t string_length()const;
	char* get_string()const;
	
};

class MyString{
	StringValue ref_string;
public:
	MyString();
	MyString(char const* string);
	MyString(const MyString& cpy);
	MyString& operator=(const MyString& cpy);
	
	char* operator+(const MyString& rhs);
	MyString& operator+=(const MyString& rhs);
	
	char* operator+(const char& rhs);
	MyString& operator+=(const char& rhs);
	
	char& operator[](size_t index);
	const char& operator[](size_t index)const;
	
	~MyString();
	
	size_t length()const;
	char* print_string()const;
	
	
	friend std::istream &operator>>(std::istream &in, MyString& str);
};

std::ostream &operator<<(std::ostream &os, MyString const& str);

#endif
