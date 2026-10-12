#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Characters {
protected:
    string name;

public:
    //конструкторы
    Characters();
    Characters(const string& name);
    Characters(const Characters& other);

    //деструктор
    virtual ~Characters();

    //гет- сет-теры
    string getName() const;
    void setName(const string& name);

    //виртуальные методы
    virtual void display() const = 0;
    virtual void edit() = 0;
    virtual void save(ofstream& file) const = 0;
    virtual string getType() const = 0;
    virtual Characters* clone() const = 0;

    //перегрузка операторов
    Characters& operator=(const Characters& other);
    friend ostream& operator<<(ostream& out,const Characters& character);
};

#endif
