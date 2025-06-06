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
        std::cout << "Nemáš žiadne potiony.\n";
        return (size_t)-1;
    }
    listPotions();
    std::cout << "Vyber číslo potionu: ";
    size_t idx;
    std::cin >> idx;
    if (idx < 1 || idx > potions.size())
    {
        std::cout << "Neplatná voľba.\n";
        return (size_t)-1;
    }
    return idx - 1;
}

void Inventory::listWeapons() const
{
    std::cout << "Zbrane v inventári:\n";
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        std::cout << i + 1 << ". " << weapons[i]->getName() << " (" << weapons[i]->getDamage() << " dmg)\n";
    }
}

void Inventory::listPotions() const
{
    std::cout << "Potiony v inventári:\n";
    for (size_t i = 0; i < potions.size(); ++i)
    {
        std::cout << i + 1 << ". Potion (+" << potions[i].use() << " HP)\n";
    }
}

Weapon *Inventory::chooseWeapon()
{
    if (weapons.empty())
    {
        std::cout << "Nemáš žiadne zbrane.\n";
        return nullptr;
    }
    listWeapons();
    std::cout << "Vyber číslo zbrane: ";
    size_t idx;
    std::cin >> idx;
    if (idx < 1 || idx > weapons.size())
    {
        std::cout << "Neplatná voľba.\n";
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