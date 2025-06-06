#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <memory>
#include "weapon.hpp"
#include "potion.hpp"

class Inventory
{
private:
    std::vector<Potion> potions;
    std::vector<std::unique_ptr<Weapon>> weapons;

public:
    void addWeapon(std::unique_ptr<Weapon> weapon);
    void addPotion(const Potion &potion);
    void removePotion(size_t idx);
    size_t choosePotionIndex();
    void listWeapons() const;
    void listPotions() const;
    Weapon *chooseWeapon();
    int usePotionAt(size_t idx);
    void printInventory() const;

    const std::vector<Potion> &getPotions() const;
    const std::vector<std::unique_ptr<Weapon>> &getWeapons() const;
    void clearPotions();
    void clearWeapons();
};

#endif