#ifndef MONSTER_H
#define MONSTER_H

#include "Characters.h"

class Monster : public Characters {
private:
    string appearance;

public:
    //конструкторы
    Monster();
    Monster(const string& name, const string& appearance);
    Monster(const Monster& other);

    //деструктор
    ~Monster() override;

    //гет- сет-теры
    string getAppearance() const;
    void setAppearance(const string& appearance);

    //виртуальные методы
    void display() const override;
    void edit() override;
    void save(ofstream& file) const override;
    string getType() const override;
    Characters* clone() const override;

    //перегрузка операторов
    Monster& operator=(const Monster& other);
};

#endif
