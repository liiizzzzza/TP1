#include "Monster.h"
#include <stdexcept>

Monster::Monster()
	: Characters(), appearance("Не указано")
{
	cout << "Monster: вызван конструктор по умолчанию" << endl;
}
Monster::Monster(const string& name, const string& appearance)
	: Characters(name), appearance(appearance)
{
	cout << "Monster: вызван конструктор с параметрами" << endl;
}
Monster::Monster(const Monster& other)
	: Characters(other), appearance(other.appearance)
{
	cout << "Monster: вызван конструктор копирования" << endl;
}
Monster::~Monster()
{
	cout << "Monster: вызван деструктор" << endl;
}
string Monster::getAppearance() const
{
	return appearance;
}
void Monster::setAppearance(const string& appearance)
{
	if (appearance.empty())
		throw invalid_argument("Описание внешнего вида не может быть пустым.");
	this->appearance = appearance;
}
void Monster::display() const
{
	cout << "Монстр: " << name << endl;
	cout << "Описание внешнего вида: " << appearance << endl;
}
void Monster::edit()
{
	string newName;
	string newAppearance;
	cout << "Введите название монстра: ";
	getline(cin >> ws, newName);
	cout << "Введите описание внешнего вида: ";
	getline(cin, newAppearance);
	setName(newName);
	setAppearance(newAppearance);
}
void Monster::save(ofstream& file) const
{
	if (!file)
		throw runtime_error("Не удалось записать данные монстра.");
	file << "Monster\n"
		<< name << '\n'
		<< appearance << '\n';
}
string Monster::getType() const
{
	return "Monster";
}
Characters* Monster::clone() const
{
	return new Monster(*this);
}
Monster& Monster::operator=(const Monster& other)
{
	if (this != &other)
	{
		Characters::operator=(other);
		appearance = other.appearance;
	}
	cout << "Monster: вызван оператор присваивания" << endl;
	return *this;
}