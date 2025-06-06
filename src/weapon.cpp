#include "weapon.hpp"

Weapon::Weapon(const std::string &name, int damage, WeaponEffect effect)
    : name(name), damage(damage), effect(effect) {}

WeaponEffect Weapon::getEffect() const { return effect; }

std::string Weapon::getName() const
{
    return name;
}

int Weapon::getDamage() const
{
    return damage;
}