#include "player.hpp"
#include "enemy.hpp"
#include <iostream>

Player::Player()
    : hp(120), xp(0), level(1), weapon(std::make_unique<Weapon>("Meč", 15))
{
    inventory.addPotion(Potion());
    inventory.addPotion(Potion());
}

int Player::getHP() const { return hp; }
int Player::getXP() const { return xp; }
int Player::getLevel() const { return level; }

void Player::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}

void Player::attack(Enemy &enemy)
{
    std::cout << "Útočíš so zbraňou " << weapon->getName() << " za " << weapon->getDamage() << " poškodenia!\n";
    enemy.takeDamage(weapon->getDamage());
}

void Player::heal()
{
    size_t idx = inventory.choosePotionIndex();
    if (idx != (size_t)-1)
    {
        int amount = inventory.usePotionAt(idx);
        hp += amount;
        if (hp > 100)
            hp = 100;
        std::cout << "Vyliečil si sa o " << amount << ", aktuálne HP: " << hp << "\n";
        inventory.removePotion(idx);
    }
    else
    {
        std::cout << "Nemáš žiadny potion na použitie.\n";
    }
}

bool Player::isAlive() const { return hp > 0; }

void Player::printStatus() const
{
    std::cout << "Hráč - HP: " << hp << ", XP: " << xp << ", Level: " << level
              << ", zbraň: " << weapon->getName() << " (" << weapon->getDamage() << " dmg)\n";
}

void Player::gainXP(int amount)
{
    xp += amount;
    std::cout << "Získal si " << amount << " XP! Aktuálne XP: " << xp << "\n";
    if (xp >= level * 100)
    {
        levelUp();
    }
}

void Player::levelUp()
{
    level++;
    xp = 0;
    hp = 100;
    std::cout << "Postúpil si na level " << level << "! HP obnovené.\n";
}

Inventory &Player::getInventory()
{
    return inventory;
}