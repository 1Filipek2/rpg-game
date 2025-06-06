#include "inventory.hpp"
#include <iostream>

void Inventory::addWeapon(std::unique_ptr<Weapon> weapon)
{
    weapons.push_back(std::move(weapon));
}

void Inventory::addPotion(const Potion &potion)
{
    potions.push_back(potion);
}

void Inventory::removePotion(size_t idx)
{
    if (idx < potions.size())
        potions.erase(potions.begin() + idx);
}

size_t Inventory::choosePotionIndex()
{
    if (potions.empty())
    {
        std::cout << "You have no potions.\n";
        return (size_t)-1;
    }
    listPotions();
    std::cout << "Choose potion number: ";
    size_t idx;
    std::cin >> idx;
    if (idx < 1 || idx > potions.size())
    {
        std::cout << "Invalid choice.\n";
        return (size_t)-1;
    }
    return idx - 1;
}

void Inventory::listWeapons() const
{
    std::cout << "Weapons in inventory:\n";
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        std::cout << i + 1 << ". " << weapons[i]->getName() << " (" << weapons[i]->getDamage() << " dmg)\n";
    }
}

void Inventory::listPotions() const
{
    std::cout << "Potions in inventory:\n";
    for (size_t i = 0; i < potions.size(); ++i)
    {
        std::cout << i + 1 << ". " << potions[i].getName() << " (+" << potions[i].use() << " HP)\n";
    }
}

Weapon *Inventory::chooseWeapon()
{
    if (weapons.empty())
    {
        std::cout << "You have no weapons.\n";
        return nullptr;
    }
    listWeapons();
    std::cout << "Choose weapon number: ";
    size_t idx;
    std::cin >> idx;
    if (idx < 1 || idx > weapons.size())
    {
        std::cout << "Invalid choice.\n";
        return nullptr;
    }
    return weapons[idx - 1].get();
}

int Inventory::usePotionAt(size_t idx)
{
    if (idx < potions.size())
        return potions[idx].use();
    return 0;
}

void Inventory::printInventory() const
{
    std::cout << "=== INVENTORY ===\n";
    std::cout << "Number of potions: " << potions.size() << "\n";
    listPotions();
    std::cout << "Number of weapons: " << weapons.size() << "\n";
    listWeapons();
    std::cout << "=================\n";
}

const std::vector<Potion> &Inventory::getPotions() const
{
    return potions;
}

const std::vector<std::unique_ptr<Weapon>> &Inventory::getWeapons() const
{
    return weapons;
}

void Inventory::clearPotions()
{
    potions.clear();
}

void Inventory::clearWeapons()
{
    weapons.clear();
}