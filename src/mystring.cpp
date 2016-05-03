#include <iostream>
#include <cstring>
#include "mystring.hpp"


///////////////////////////////CLASS_STRINGVALUE///////////////////////////////////////////////////////////

/**Ha nem kap stringet üresre incicializálódik*/
StringValue::StringValue():strData{nullptr}, ref_count{nullptr}{}
	
/**Karaktertömb konstruktor: értékül adott stringnek megfelelő méretű helyet foglal, átmásolja a lefoglalt területre. 
 * Ha nem üres a string a referenciaszámlálót 1-be állítja */
StringValue::StringValue(char const* string){
	strData = new char[strlen(string) + 1];
	strcpy(strData, string);
	if(strData)
		ref_count = new size_t{1};
	else
		ref_count = nullptr;
}

/** Cpy Konst. Az aktuális objektum értékét megfelelteti az értékül adottéval és növeli a referencia számlálót*/
StringValue::StringValue(StringValue const& newref):strData{newref.strData}, ref_count{newref.ref_count}{
	++ *ref_count;
}

/** Egyenlőség op. == CpyConstr*/
StringValue& StringValue::operator=(StringValue const& rhs){
	this->strData = rhs.strData;
	this->ref_count = rhs.ref_count;
	 ++ *ref_count;
	return *this;
}
/** Destruktor. Ha van adat(== van hivatkozás) a tárolóban akkor csökkentjük a referencia számot.
 * Ha a referencia számáló eléri a nullát felszabadítjuk mivel nincs több hivatkozás az adatokra*/
StringValue::~StringValue(){
	
	if(strData){
		std::cout<<"||||---> " << "(1)lefutott: " << strData << " : "  <<  *ref_count << "(régi ref. szám)" <<std::endl;
		-- *ref_count;
		if(*ref_count == 0){
			delete strData;
			delete ref_count;
			}
		std::cout<<"||||---> " << "(2)lefutott: "<< strData << " : " << *ref_count << "(új ref. szám)"<<std::endl;
		}
	
	}

size_t StringValue::string_length() const{
	return strlen(strData);
}	
	
char* StringValue::get_string()const{
	return strData;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////CLASS_MYSTRING/////////////////////////////////////////////////////////
MyString::MyString() :ref_string{StringValue()}{
}

/**String konstruktor. A megadott karaktertömbböt továbbadja a StringValue
 * konstruktorának beállítva az értéket és a referencia számlálót*/
MyString::MyString(char const* string) :ref_string{StringValue(string)}{
}

/**Másoló Ctor. Az aktuális objektumunk adattagja egyenlő lesz a másolandóéval
 * és az egyenlőség operátor elvégzi a referenciaszám növelését*/
MyString::MyString(const MyString& cpy){
	ref_string = cpy.ref_string;
}

/** Olyan módon működik mint a Másoló Ctor*/
MyString& MyString::operator=(const MyString& cpy){
	ref_string.~StringValue();
	ref_string = cpy.ref_string;
	return *this;
}

/**Plusz operátor. A két MyString objektum összefűzött adattagját adja vissza karaktertömb
 * formában, így a értékül kapott sztringre konstruktor hívódik*/
char* MyString::operator+(const MyString& rhs){
	size_t len = length() + rhs.length();
	char * new_str = new char[len + 1];
	strcpy(new_str, ref_string.get_string());
	strcat(new_str, rhs.print_string());
	std::cout << new_str << std::endl;
	return new_str;
}	

/** += operátor. Működése hasonló a +operátoréhoz, viszont a régi adatagra
 * dtor-t kell hívni, mivel a művelet hatására új sztring jön létre így a régire már nem hivatkozunk*/
MyString& MyString::operator+=(const MyString& rhs){
	char *temp = *this + rhs;
	ref_string.~StringValue();
	ref_string = temp;
	return *this;
}	

/** az aktuális string méretéhez hozzáadunk egyet és ezt kitöltjük
 * a kapott karakterrel, ezért ismét charakterömbként adjuk, vissza hogy konstruktor hívódjon rá*/
char* MyString::operator+(const char& rhs){
	size_t len = length() + 1;
	char *temp = new char[len + 1];
	strcpy(temp, ref_string.get_string());
	temp[len-1] = rhs;
	temp[len] = '\0';
	return temp; 
}

/**pont mint a sima karaker + operátornál, és ismét destruktort hívunk mert megszűnik a hivatkozás*/
MyString& MyString::operator+=(const char& rhs){
	char *temp = *this + rhs;
	ref_string.~StringValue();
	ref_string = temp;
	return *this;
}

/***/
char& MyString::operator[](size_t index){
	char *temp = ref_string.get_string();
	if(index <= ref_string.string_length())
		return temp[index];
	else
		return temp[0];
}

const char& MyString::operator[](size_t index)const{
	char *temp = ref_string.get_string();
	if(index <= ref_string.string_length())
		return temp[index];
	else
		return temp[0];
}

char* MyString::print_string() const{
	return ref_string.get_string();
}

size_t MyString::length() const{
	return ref_string.string_length();
}

MyString::~MyString(){
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, MyString const& str){
	char* temp = str.print_string();
	os << temp << " ---mem cim---> " << &temp << std::endl;
	return os;
}

std::istream &operator>>(std::istream &in, MyString& str){
	char buff[256];
	
	in.get(buff, 256);
	str.ref_string = buff;
	
	return in;
}
