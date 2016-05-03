#include "mystring.hpp"
#include <iostream>
int main(){
	
	MyString egyes = "egyes String";
	MyString *kettes = new MyString("kettes String");
	MyString egyes_cpy = egyes;
	MyString temp;
	
	std::cout << egyes << std::endl;
	std::cout << *kettes << std::endl;
	std::cout << egyes_cpy << std::endl;
	
	temp = egyes + egyes_cpy;
	std::cout << temp << std::endl;
	
	temp += egyes;
	std::cout << temp << std::endl;
	
	temp += 'Q';
	std::cout << temp << std::endl;
	
	
	delete kettes;
}
