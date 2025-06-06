#include "enemy.hpp"
#include "player.hpp"
#include <iostream>

Enemy::Enemy(const std::string &name, int hp, int damage)
    : name(name), hp(hp), damage(damage) {}

std::string Enemy::getName() const
{
    return name;
}

int Enemy::getHP() const
{
    return hp;
}

void Enemy::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}

void Enemy::attack(Player &player)
{
    std::cout << name << " útočí za " << damage << " poškodenia!\n";
    player.takeDamage(damage);
}

bool Enemy::isAlive() const
{
    return hp > 0;
}