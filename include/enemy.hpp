#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>

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

    virtual std::string getName() const;
    virtual int getHP() const;
    virtual void takeDamage(int dmg);
    virtual void attack(Player &player);
    virtual bool isAlive() const;
};

#endif