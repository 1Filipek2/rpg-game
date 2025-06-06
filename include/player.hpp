#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "weapon.hpp"
#include "potion.hpp"
#include "inventory.hpp"
#include <memory>
#include <string>

class Player
{
private:
    int hp;
    int xp;
    int level;
    std::unique_ptr<Weapon> weapon;
    Inventory inventory;

public:
    Player();

    int getHP() const;
    int getXP() const;
    int getLevel() const;
    void takeDamage(int dmg);
    void attack(class Enemy &enemy);
    void heal();
    bool isAlive() const;
    void printStatus() const;

    void gainXP(int amount);
    void levelUp();

    Inventory &getInventory();
};

#endif