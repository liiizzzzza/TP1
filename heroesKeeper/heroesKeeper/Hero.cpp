#include "Hero.h"
#include <stdexcept>
#include <limits>

Hero::Hero()
	: Characters(), weaponType("Не указано"),
	skills(nullptr), skillCount(0)
{
	cout << "Hero: вызван конструктор по умолчанию" << endl;
}
Hero::Hero(const string& name, const string& weaponType,
	const string* skills, int skillCount)
	: Characters(name), weaponType(weaponType),
	skills(nullptr), skillCount(0)
{
	setSkills(skills, skillCount);
	cout << "Hero: вызван конструктор с параметрами" << endl;
}
Hero::Hero(const Hero& other)
	: Characters(other), weaponType(other.weaponType),
	skills(nullptr), skillCount(0)
{
	setSkills(other.skills, other.skillCount);
	cout << "Hero: вызван конструктор копирования" << endl;
}
Hero::~Hero()
{
	delete[] skills;
	cout << "Hero: вызван деструктор" << endl;
}
string Hero::getWeaponType() const
{
	return weaponType;
}
void Hero::setWeaponType(const string& weaponType)
{
	if (weaponType.empty())
		throw invalid_argument("Тип оружия не может быть пустым.");
	this->weaponType = weaponType;
}
int Hero::getSkillCount() const
{
	return skillCount;
}
string Hero::getSkill(int index) const
{
	if (index < 0 || index >= skillCount)
		throw out_of_range("Неверный индекс навыка героя.");
	return skills[index];
}
void Hero::setSkills(const string* newSkills, int count)
{
	if (count < 0 || (count > 0 && newSkills == nullptr))
		throw invalid_argument("Некорректные данные навыков героя.");
	string* temp = nullptr;
	if (count > 0)
	{
		temp = new string[count];
		for (int i = 0; i < count; i++)
			temp[i] = newSkills[i];
	}
	delete[] skills;
	skills = temp;
	skillCount = count;
}
void Hero::display() const
{
	cout << "Герой: " << name << endl;
	cout << "Тип оружия: " << weaponType << endl;
	cout << "Основные навыки:" << endl;
	for (int i = 0; i < skillCount; i++)
		cout << "  " << i + 1 << ". " << skills[i] << endl;
}
void Hero::edit()
{
	string newName, newWeapon;
	int count;
	cout << "Введите имя героя: ";
	getline(cin >> ws, newName);
	cout << "Введите тип оружия: ";
	getline(cin, newWeapon);
	cout << "Введите количество навыков: ";
	if (!(cin >> count))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Количество навыков должно быть числом.");
	}
	if (count < 0 || count > 100)
		throw invalid_argument("Количество навыков должно быть от 0 до 100.");
	string* newSkills = count > 0 ? new string[count] : nullptr;
	try
	{
		for (int i = 0; i < count; i++)
		{
			cout << "Введите навык " << i + 1 << ": ";
			getline(cin >> ws, newSkills[i]);
		}
		setName(newName);
		setWeaponType(newWeapon);
		setSkills(newSkills, count);
	}
	catch (...)
	{
		delete[] newSkills;
		throw;
	}
	delete[] newSkills;
}
void Hero::save(ofstream& file) const
{
	if (!file)
		throw runtime_error("Не удалось записать данные героя.");
	file << "Hero\n"
		<< name << '\n'
		<< weaponType << '\n'
		<< skillCount << '\n';
	for (int i = 0; i < skillCount; i++)
		file << skills[i] << '\n';
}
string Hero::getType() const
{
	return "Hero";
}
Characters* Hero::clone() const
{
	return new Hero(*this);
}
Hero& Hero::operator=(const Hero& other)
{
	if (this != &other)
	{
		string* temp = nullptr;
		if (other.skillCount > 0)
		{
			temp = new string[other.skillCount];
			for (int i = 0; i < other.skillCount; i++)
				temp[i] = other.skills[i];
		}
		Characters::operator=(other);
		weaponType = other.weaponType;
		delete[] skills;
		skills = temp;
		skillCount = other.skillCount;
	}
	cout << "Hero: вызван оператор присваивания" << endl;
	return *this;
}