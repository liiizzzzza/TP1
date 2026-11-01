
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <clocale>
#include <memory>

#define NOMINMAX
#include <Windows.h>

#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"

using namespace std;

// Ввод целого числа с проверкой
int readInt(const string& message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Ошибка: необходимо ввести целое число." << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Ввод строки
string readString(const string& message)
{
    cout << message;

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    wchar_t buffer[1024];
    DWORD charsRead = 0;

    if (!ReadConsoleW(hInput, buffer, 1024, &charsRead, nullptr))
    {
        throw runtime_error("Ошибка чтения строки из консоли.");
    }

    // Убираем символы переноса строки
    while (charsRead > 0 &&
        (buffer[charsRead - 1] == L'\n' ||
            buffer[charsRead - 1] == L'\r'))
    {
        charsRead--;
    }

    // Определяем размер строки в UTF-8
    int size = WideCharToMultiByte(
        CP_UTF8, 0,
        buffer, charsRead,
        nullptr, 0,
        nullptr, nullptr
    );

    string result(size, '\0');

    // Преобразуем Unicode в UTF-8
    if (size > 0)
    {
        WideCharToMultiByte(
            CP_UTF8, 0,
            buffer, charsRead,
            &result[0], size,
            nullptr, nullptr
        );
    }

    return result;
}

// Ввод нескольких навыков
string* readSkills(int& skillCount)
{
    skillCount = readInt("Введите количество навыков: ");

    if (skillCount < 0 || skillCount > 100)
        throw invalid_argument("Количество навыков должно быть от 0 до 100.");

    string* skills = skillCount > 0 ? new string[skillCount] : nullptr;

    try
    {
        for (int i = 0; i < skillCount; i++)
        {
            skills[i] = readString(
                "Введите навык " + to_string(i + 1) + ": "
            );
        }
    }
    catch (...)
    {
        delete[] skills;
        throw;
    }

    return skills;
}

// Создание героя
Characters* createHero()
{
    string name = readString("Введите имя героя: ");
    string weapon = readString("Введите тип оружия: ");

    int skillCount;
    string* skills = readSkills(skillCount);

    try
    {
        Characters* hero = new Hero(name, weapon, skills, skillCount);

        delete[] skills;
        return hero;
    }
    catch (...)
    {
        delete[] skills;
        throw;
    }
}

// Создание злодея
Characters* createVillain()
{
    string name = readString("Введите имя злодея: ");
    string weapon = readString("Введите тип оружия: ");
    string crime = readString("Введите совершённое злодеяние: ");
    string habitat = readString("Введите место обитания: ");

    int skillCount;
    string* skills = readSkills(skillCount);

    try
    {
        Characters* villain = new Villain(
            name, weapon, crime, habitat, skills, skillCount
        );

        delete[] skills;
        return villain;
    }
    catch (...)
    {
        delete[] skills;
        throw;
    }
}

// Создание монстра
Characters* createMonster()
{
    string name = readString("Введите название монстра: ");
    string appearance = readString("Введите описание внешнего вида: ");

    return new Monster(name, appearance);
}

// Добавление персонажа
void addCharacter(Keeper& keeper)
{
    cout << "\nВыберите тип персонажа:" << endl;
    cout << "1. Герой" << endl;
    cout << "2. Злодей" << endl;
    cout << "3. Монстр" << endl;

    int choice = readInt("Ваш выбор: ");

    Characters* character = nullptr;

    switch (choice)
    {
    case 1:
        character = createHero();
        break;

    case 2:
        character = createVillain();
        break;

    case 3:
        character = createMonster();
        break;

    default:
        throw invalid_argument("Такого типа персонажа нет.");
    }

    try
    {
        keeper.add(character);
    }
    catch (...)
    {
        delete character;
        throw;
    }
}

// Редактирование выбранного персонажа
void editSelectedCharacter(Keeper& keeper)
{
    if (keeper.getCount() == 0)
    {
        cout << "Список персонажей пуст." << endl;
        return;
    }

    keeper.displayAll();

    int characterNumber = readInt(
        "Введите номер персонажа для редактирования: "
    );

    Characters* selectedCharacter = keeper.getCharacter(characterNumber - 1);

    // Редактирование героя
    if (Hero* hero = dynamic_cast<Hero*>(selectedCharacter))
    {
        string newName = readString("Введите имя героя: ");
        string newWeaponType = readString("Введите тип оружия: ");

        int skillCount;
        unique_ptr<string[]> newSkills(readSkills(skillCount));

        hero->setName(newName);
        hero->setWeaponType(newWeaponType);
        hero->setSkills(newSkills.get(), skillCount);
    }
    // Редактирование злодея
    else if (Villain* villain = dynamic_cast<Villain*>(selectedCharacter))
    {
        string newName = readString("Введите имя злодея: ");
        string newWeaponType = readString("Введите тип оружия: ");
        string newCrime = readString("Введите совершённое злодеяние: ");
        string newHabitat = readString("Введите место обитания: ");

        int skillCount;
        unique_ptr<string[]> newSkills(readSkills(skillCount));

        villain->setName(newName);
        villain->setWeaponType(newWeaponType);
        villain->setCrime(newCrime);
        villain->setHabitat(newHabitat);
        villain->setSkills(newSkills.get(), skillCount);
    }
    // Редактирование монстра
    else if (Monster* monster = dynamic_cast<Monster*>(selectedCharacter))
    {
        string newName = readString("Введите название монстра: ");
        string newAppearance = readString(
            "Введите описание внешнего вида: "
        );

        monster->setName(newName);
        monster->setAppearance(newAppearance);
    }

    cout << "Данные персонажа изменены." << endl;
}

// Вывод меню
void showMenu()
{
    cout << "\n========== МЕНЮ ==========" << endl;
    cout << "1. Добавить персонажа" << endl;
    cout << "2. Показать всех персонажей" << endl;
    cout << "3. Редактировать персонажа" << endl;
    cout << "4. Удалить персонажа" << endl;
    cout << "5. Сохранить коллекцию в файл" << endl;
    cout << "6. Загрузить коллекцию из файла" << endl;
    cout << "0. Выход" << endl;
    cout << "=========================" << endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    Keeper keeper;

    bool running = true;

    while (running)
    {
        try
        {
            showMenu();

            int choice = readInt("Выберите действие: ");

            switch (choice)
            {
            case 1:
                addCharacter(keeper);
                break;

            case 2:
                keeper.displayAll();
                break;

            case 3:
                editSelectedCharacter(keeper);
                break;

            case 4:
            {
                if (keeper.getCount() == 0)
                {
                    cout << "Список персонажей пуст." << endl;
                    break;
                }

                keeper.displayAll();

                int characterNumber = readInt(
                    "Введите номер персонажа для удаления: "
                );

                keeper.remove(characterNumber - 1);
                break;
            }

            case 5:
            {
                string filename = readString(
                    "Введите имя файла для сохранения: "
                );

                keeper.saveToFile(filename);
                break;
            }

            case 6:
            {
                string filename = readString(
                    "Введите имя файла для загрузки: "
                );

                keeper.loadFromFile(filename);
                break;
            }

            case 0:
                running = false;
                cout << "Завершение программы." << endl;
                break;

            default:
                cout << "Ошибка: такого пункта меню нет." << endl;
                break;
            }
        }
        catch (const exception& e)
        {
            cout << "\nИсключительная ситуация: "
                << e.what() << endl;
        }
    }

    return 0;
}
