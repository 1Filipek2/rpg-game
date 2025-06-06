#ifndef POTION_HPP
#define POTION_HPP

#include <string>

enum class PotionType
{
    Small,
    Large,
    Special
};

class Potion
{
    PotionType type;
    int healAmount;

public:
    Potion(PotionType type = PotionType::Small);
    int use() const;
    std::string getName() const;
    PotionType getType() const;
};

#endif