#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
private:
    std::string name;
    int damage;

public:
    Weapon(const std::string &name, int damage);
    std::string getName() const;
    int getDamage() const;
};

#endif