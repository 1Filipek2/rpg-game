#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <memory>
#include "potion.hpp"
#include "weapon.hpp"

class Inventory
{
private:
    std::vector<Potion> potions;
    std::vector<std::unique_ptr<Weapon>> weapons;

public:
    void addPotion(const Potion &potion);
    void addWeapon(std::unique_ptr<Weapon> weapon);
    void removePotion(size_t idx);
    size_t choosePotionIndex();
    void listPotions() const;
    void listWeapons() const;
    Weapon *chooseWeapon();
    int usePotionAt(size_t idx);
};

#endif