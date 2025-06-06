#include "potion.hpp"
#include <random>

Potion::Potion()
{
    healingAmount = 30;
}

int Potion::use() const
{
    return healingAmount;
}