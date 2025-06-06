#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

enum class WeaponEffect
{
    None,
    Critical,
    Stun
};

class Weapon
{
private:
    std::string name;
    int damage;
    WeaponEffect effect;

public:
    Weapon(const std::string &name, int damage, WeaponEffect effect = WeaponEffect::None);
    int getDamage() const;
    std::string getName() const;
    WeaponEffect getEffect() const;
};

#endif