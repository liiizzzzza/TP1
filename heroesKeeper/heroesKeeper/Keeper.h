#ifndef KEEPER_H
#define KEEPER_H

#include "Characters.h"

class Keeper {
private:
    Characters** characters;
    int count;
    int capacity;

    //изменение размера массива
    void resize(int newCapacity);

public:
    //конструкторы
    Keeper();
    Keeper(const Keeper& other);

    //деструктор
    ~Keeper();

    //перегрузка операторов
    Keeper& operator=(const Keeper& other);

    //гет- сет-теры
    int getCount() const;
    Characters* getCharacter(int index) const;

    //управление объектами
    void add(Characters* character);
    void remove(int index);
    void displayAll() const;
    void editCharacter(int index);
    void clear();

    //сохранение и восстановление коллекции
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif
