#include "Characters.h"
#include <stdexcept>
Characters::Characters() : name("Без имени")
{
	cout << "Characters: вызван конструктор по умолчанию" << endl;
}
Characters::Characters(const string& name) : name(name)
{
	cout << "Characters: вызван конструктор с параметрами" << endl;
}
Characters::Characters(const Characters& other) : name(other.name)
{
	cout << "Characters: вызван конструктор копирования" << endl;
}
Characters::~Characters()
{
	cout << "Characters: вызван деструктор" << endl;
}
string Characters::getName() const
{
	return name;
}
void Characters::setName(const string& name)
{
	if (name.empty())
		throw invalid_argument("Имя персонажа не может быть пустым.");
	this->name = name;
}
Characters& Characters::operator=(const Characters& other)
{
	if (this != &other)
		name = other.name;
	cout << "Characters: вызван оператор присваивания" << endl;
	return *this;
}
ostream& operator<<(ostream& out, const Characters& character)
{
	out << "Тип персонажа: " << character.getType()
		<< ", имя: " << character.getName();
	return out;
}