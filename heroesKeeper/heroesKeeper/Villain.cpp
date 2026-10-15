#include "Villain.h"
#include <stdexcept>
#include <limits>

Villain::Villain()
	: Characters(), weaponType("Не указано"),
	crime("Не указано"), habitat("Не указано"),
	skills(nullptr), skillCount(0)
{
	cout << "Villain: вызван конструктор по умолчанию" << endl;
}
Villain::Villain(const string& name, const string& weaponType,
	const string& crime, const string& habitat,
	const string* skills, int skillCount)
	: Characters(name), weaponType(weaponType),
	crime(crime), habitat(habitat),
	skills(nullptr), skillCount(0)
{
	setSkills(skills, skillCount);
	cout << "Villain: вызван конструктор с параметрами" << endl;
}
Villain::Villain(const Villain& other)
	: Characters(other), weaponType(other.weaponType),
	crime(other.crime), habitat(other.habitat),
	skills(nullptr), skillCount(0)
{
	setSkills(other.skills, other.skillCount);
	cout << "Villain: вызван конструктор копирования" << endl;
}
Villain::~Villain()
{
	delete[] skills;
	cout << "Villain: вызван деструктор" << endl;
}
string Villain::getWeaponType() const
{
	return weaponType;
}
void Villain::setWeaponType(const string& weaponType)
{
	if (weaponType.empty())
		throw invalid_argument("Тип оружия не может быть пустым.");
	this->weaponType = weaponType;
}
string Villain::getCrime() const
{
	return crime;
}
void Villain::setCrime(const string& crime)
{
	if (crime.empty())
		throw invalid_argument("Описание злодеяния не может быть пустым.");
	this->crime = crime;
}
string Villain::getHabitat() const
{
	return habitat;
}
void Villain::setHabitat(const string& habitat)
{
	if (habitat.empty())
		throw invalid_argument("Место обитания не может быть пустым.");
	this->habitat = habitat;
}
int Villain::getSkillCount() const
{
	return skillCount;
}
string Villain::getSkill(int index) const
{
	if (index < 0 || index >= skillCount)
		throw out_of_range("Неверный индекс навыка злодея.");
	return skills[index];
}
void Villain::setSkills(const string* newSkills, int count)
{
	if (count < 0 || (count > 0 && newSkills == nullptr))
		throw invalid_argument("Некорректные данные навыков злодея.");
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
void Villain::display() const
{
	cout << "Злодей: " << name << endl;
	cout << "Тип оружия: " << weaponType << endl;
	cout << "Совершённое злодеяние: " << crime << endl;
	cout << "Место обитания: " << habitat << endl;
	cout << "Основные навыки:" << endl;
	for (int i = 0; i < skillCount; i++)
		cout << "  " << i + 1 << ". " << skills[i] << endl;
}
void Villain::edit()
{
	string newName, newWeapon, newCrime, newHabitat;
	int count;
	cout << "Введите имя злодея: ";
	getline(cin >> ws, newName);
	cout << "Введите тип оружия: ";
	getline(cin, newWeapon);
	cout << "Введите совершённое злодеяние: ";
	getline(cin, newCrime);
	cout << "Введите место обитания: ";
	getline(cin, newHabitat);
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
		setCrime(newCrime);
		setHabitat(newHabitat);
		setSkills(newSkills, count);
	}
	catch (...)
	{
		delete[] newSkills;
		throw;
	}
	delete[] newSkills;
}
void Villain::save(ofstream& file) const
{
	if (!file)
		throw runtime_error("Не удалось записать данные злодея.");
	file << "Villain\n"
		<< name << '\n'
		<< weaponType << '\n'
		<< crime << '\n'
		<< habitat << '\n'
		<< skillCount << '\n';
	for (int i = 0; i < skillCount; i++)
		file << skills[i] << '\n';
}
string Villain::getType() const
{
	return "Villain";
}
Characters* Villain::clone() const
{
	return new Villain(*this);
}
Villain& Villain::operator=(const Villain& other)
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
		crime = other.crime;
		habitat = other.habitat;
		delete[] skills;
		skills = temp;
		skillCount = other.skillCount;
	}
	cout << "Villain: вызван оператор присваивания" << endl;
	return *this;
}