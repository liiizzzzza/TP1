#ifndef VILLAIN_H
#define VILLAIN_H

#include "Characters.h"

class Villain : public Characters {
private:
    string weaponType;
    string crime;
    string habitat;
    string* skills;
    int skillCount;

public:
    //конструкторы
    Villain();
    Villain(const string& name, const string& weaponType,
        const string& crime, const string& habitat,
        const string* skills, int skillCount);
    Villain(const Villain& other);

    //деструктор
    ~Villain() override;

    //гет- сет-теры
    string getWeaponType() const;
    void setWeaponType(const string& weaponType);

    string getCrime() const;
    void setCrime(const string& crime);

    string getHabitat() const;
    void setHabitat(const string& habitat);

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
    Villain& operator=(const Villain& other);
};

#endif
