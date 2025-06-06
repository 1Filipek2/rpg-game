#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include "weapon.hpp"
#include "inventory.hpp"

class Enemy;

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

    void setHP(int val);
    void setXP(int val);
    void setLevel(int val);

    void takeDamage(int dmg);
    void chooseWeapon();
    void attack(Enemy &enemy);
    void heal();
    bool isAlive() const;
    void printStatus() const;
    void gainXP(int amount);
    void levelUp();

    Inventory &getInventory();
    const Inventory &getInventory() const;

    std::unique_ptr<Weapon> &getWeapon();
    const std::unique_ptr<Weapon> &getWeapon() const;
    void setWeapon(std::unique_ptr<Weapon> wpn);
};

#endif