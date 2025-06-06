#include "potion.hpp"
#include <random>

Potion::Potion(PotionType type) : type(type)
{
    switch (type)
    {
    case PotionType::Small:
        healAmount = 20;
        break;
    case PotionType::Large:
        healAmount = 50;
        break;
    case PotionType::Special:
        healAmount = 30;
        break;
    }
}

int Potion::use() const { return healAmount; }

std::string Potion::getName() const
{
    switch (type)
    {
    case PotionType::Small:
        return "Small Potion";
    case PotionType::Large:
        return "Large Potion";
    case PotionType::Special:
        return "Special Potion";
    }
    return "Unknown";
}

PotionType Potion::getType() const { return type; }