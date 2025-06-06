#include "enemy.hpp"
#include "player.hpp"
#include <iostream>

Enemy::Enemy(const std::string &name, int hp, int damage)
    : name(name), hp(hp), damage(damage) {}

void Enemy::attack(Player &player)
{
    std::cout << name << " attacks for " << damage << " damage!\n";
    player.takeDamage(damage);
}

void Enemy::specialAbility(Player &player)
{
    // Basic enemy has no special ability
}

std::string Enemy::getName() const { return name; }
int Enemy::getHP() const { return hp; }
bool Enemy::isAlive() const { return hp > 0; }
void Enemy::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}