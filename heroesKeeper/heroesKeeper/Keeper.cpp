
#include "Keeper.h"
#include "Hero.h"
#include "Villain.h"
#include "Monster.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>

using namespace std;

// Конструктор по умолчанию
Keeper::Keeper()
    : characters(nullptr), count(0), capacity(0)
{
    cout << "Keeper: вызван конструктор по умолчанию" << endl;
}

// Конструктор копирования
Keeper::Keeper(const Keeper& other)
    : characters(nullptr), count(0), capacity(0)
{
    cout << "Keeper: вызван конструктор копирования" << endl;

    if (other.count > 0)
    {
        characters = new Characters * [other.count]();
        capacity = other.count;

        try
        {
            for (int i = 0; i < other.count; i++)
            {
                characters[i] = other.characters[i]->clone();
                count++;
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }
}

// Деструктор
Keeper::~Keeper()
{
    clear();
    cout << "Keeper: вызван деструктор" << endl;
}

// Изменение размера динамического массива
void Keeper::resize(int newCapacity)
{
    if (newCapacity < count)
        throw invalid_argument(
            "Новая вместимость не может быть меньше количества персонажей."
        );

    if (newCapacity == capacity)
        return;

    Characters** temp = newCapacity > 0
        ? new Characters * [newCapacity]()
        : nullptr;

    for (int i = 0; i < count; i++)
        temp[i] = characters[i];

    delete[] characters;

    characters = temp;
    capacity = newCapacity;
}

// Оператор присваивания
Keeper& Keeper::operator=(const Keeper& other)
{
    if (this == &other)
        return *this;

    Characters** temp = other.count > 0
        ? new Characters * [other.count]()
        : nullptr;

    int copied = 0;

    try
    {
        for (int i = 0; i < other.count; i++)
        {
            temp[i] = other.characters[i]->clone();
            copied++;
        }
    }
    catch (...)
    {
        for (int i = 0; i < copied; i++)
            delete temp[i];

        delete[] temp;
        throw;
    }

    clear();

    delete[] characters;
    characters = temp;
    count = other.count;
    capacity = other.count;

    cout << "Keeper: вызван оператор присваивания" << endl;

    return *this;
}

// Получение количества персонажей
int Keeper::getCount() const
{
    return count;
}

// Получение персонажа по индексу
Characters* Keeper::getCharacter(int index) const
{
    if (index < 0 || index >= count)
        throw out_of_range("Неверный индекс персонажа.");

    return characters[index];
}

// Добавление персонажа
void Keeper::add(Characters* character)
{
    if (character == nullptr)
        throw invalid_argument("Нельзя добавить пустого персонажа.");

    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 2 : capacity * 2;
        resize(newCapacity);
    }

    characters[count] = character;
    count++;

    cout << "Персонаж добавлен в Keeper." << endl;
}

// Удаление персонажа
void Keeper::remove(int index)
{
    if (index < 0 || index >= count)
        throw out_of_range("Неверный индекс для удаления персонажа.");

    delete characters[index];

    for (int i = index; i < count - 1; i++)
        characters[i] = characters[i + 1];

    characters[count - 1] = nullptr;
    count--;

    cout << "Персонаж удалён." << endl;
}

// Вывод всех персонажей
void Keeper::displayAll() const
{
    if (count == 0)
    {
        cout << "Список персонажей пуст." << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        cout << "\nПерсонаж №" << i + 1 << endl;
        characters[i]->display();
    }
}

// Редактирование персонажа
void Keeper::editCharacter(int index)
{
    if (index < 0 || index >= count)
        throw out_of_range("Неверный индекс персонажа для редактирования.");

    characters[index]->edit();
}

// Очистка коллекции
void Keeper::clear()
{
    for (int i = 0; i < count; i++)
    {
        delete characters[i];
        characters[i] = nullptr;
    }

    delete[] characters;

    characters = nullptr;
    count = 0;
    capacity = 0;
}

// Сохранение коллекции в файл
void Keeper::saveToFile(const string& filename) const
{
    ofstream file(filename);

    if (!file)
        throw runtime_error("Не удалось открыть файл для сохранения.");

    file << count << '\n';

    for (int i = 0; i < count; i++)
        characters[i]->save(file);

    if (!file)
        throw runtime_error("Ошибка при записи данных в файл.");

    cout << "Коллекция успешно сохранена в файл "
        << filename << endl;
}

// Загрузка коллекции из файла
void Keeper::loadFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file)
        throw runtime_error("Не удалось открыть файл для загрузки.");

    int newCount;

    if (!(file >> newCount) || newCount < 0)
        throw runtime_error("Некорректное количество персонажей в файле.");

    file.ignore(numeric_limits<streamsize>::max(), '\n');

    Characters** temp = newCount > 0
        ? new Characters * [newCount]()
        : nullptr;

    int loaded = 0;

    try
    {
        for (int i = 0; i < newCount; i++)
        {
            string type;

            if (!getline(file, type))
                throw runtime_error("Не удалось прочитать тип персонажа.");

            if (type == "Hero")
                temp[i] = new Hero();
            else if (type == "Villain")
                temp[i] = new Villain();
            else if (type == "Monster")
                temp[i] = new Monster();
            else
                throw runtime_error(
                    "Неизвестный тип персонажа: " + type
                );

            temp[i]->load(file);
            loaded++;
        }
    }
    catch (...)
    {
        for (int i = 0; i < newCount; i++)
            delete temp[i];

        delete[] temp;
        throw;
    }

    // Заменяем старую коллекцию после успешной загрузки.
    clear();

    characters = temp;
    count = loaded;
    capacity = newCount;

    cout << "Коллекция успешно загружена из файла "
        << filename << endl;
}
