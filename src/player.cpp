#include "player.hpp"
#include "enemy.hpp"
#include <iostream>
#include "colors.hpp"

Player::Player()
    : hp(120), xp(0), level(1), weapon(std::make_unique<Weapon>("Sword", 15))
{
    inventory.addPotion(Potion());
    inventory.addPotion(Potion());
}

int Player::getHP() const { return hp; }
int Player::getXP() const { return xp; }
int Player::getLevel() const { return level; }

void Player::setHP(int val) { hp = val; }
void Player::setXP(int val) { xp = val; }
void Player::setLevel(int val) { level = val; }

std::unique_ptr<Weapon> &Player::getWeapon() { return weapon; }
const std::unique_ptr<Weapon> &Player::getWeapon() const { return weapon; }
Inventory &Player::getInventory() { return inventory; }
const Inventory &Player::getInventory() const { return inventory; }

void Player::setWeapon(std::unique_ptr<Weapon> wpn) { weapon = std::move(wpn); }

void Player::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}

void Player::chooseWeapon()
{
    Weapon *selected = inventory.chooseWeapon();
    if (selected)
    {
        weapon = std::make_unique<Weapon>(*selected);
        std::cout << COLOR_CYAN << "Selected weapon: " << weapon->getName() << " (" << weapon->getDamage() << " dmg)\n"
                  << COLOR_RESET;
    }
}

void Player::attack(Enemy &enemy)
{
    std::cout << COLOR_YELLOW << "You attack with " << weapon->getName() << " for " << weapon->getDamage() << " damage!\n"
              << COLOR_RESET;
    int totalDamage = weapon->getDamage();
    if (weapon->getEffect() == WeaponEffect::Critical && (rand() % 100) < 20)
    {
        std::cout << COLOR_MAGENTA << "Critical hit!\n"
                  << COLOR_RESET;
        totalDamage *= 2;
    }
    enemy.takeDamage(totalDamage);
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
        std::cout << COLOR_GREEN << "You healed for " << amount << ", current HP: " << hp << COLOR_RESET << "\n";
        inventory.removePotion(idx);
    }
    else
    {
        std::cout << COLOR_RED << "You have no potions to use.\n"
                  << COLOR_RESET;
    }
}

bool Player::isAlive() const { return hp > 0; }

void Player::printStatus() const
{
    std::cout << COLOR_CYAN << "Player - HP: " << hp << ", XP: " << xp << ", Level: " << level
              << ", weapon: " << weapon->getName() << " (" << weapon->getDamage() << " dmg)\n"
              << COLOR_RESET;
}

void Player::gainXP(int amount)
{
    xp += amount;
    std::cout << COLOR_YELLOW << "You gained " << amount << " XP! Current XP: " << xp << COLOR_RESET << "\n";
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
    std::cout << COLOR_GREEN << "You leveled up to level " << level << "! HP restored.\n"
              << COLOR_RESET;
}