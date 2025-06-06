#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <iostream>

class Player;

class Enemy
{
protected:
    std::string name;
    int hp;
    int damage;

public:
    Enemy(const std::string &name, int hp, int damage);
    virtual ~Enemy() = default;

    virtual void attack(Player &player);
    virtual void specialAbility(Player &player); // special ability
    std::string getName() const;
    int getHP() const;
    bool isAlive() const;
    void takeDamage(int dmg);
};

#endif