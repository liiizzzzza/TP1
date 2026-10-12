#ifndef HERO_H
#define HERO_H

#include "Characters.h"

class Hero : public Characters {
private:
    string weaponType;
    string* skills;
    int skillCount;

public:
    //конструкторы
    Hero();
    Hero(const string& name, const string& weaponType,
        const string* skills, int skillCount);
    Hero(const Hero& other);

    //деструктор
    ~Hero() override;

    //гет- сет-теры
    string getWeaponType() const;
    void setWeaponType(const string& weaponType);

    int getSkillCount() const;
    string getSkill(int index) const;
    void setSkills(const string* skills, int skillCount);

    //виртуальные методы
    void display() const override;
    void edit() override;
    void save(ofstream& file) const override;
    string getType() const override;
    Characters* clone() const override;

    //перегрузка операторов
    Hero& operator=(const Hero& other);
};

#endif
