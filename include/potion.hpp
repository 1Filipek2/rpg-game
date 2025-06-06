#ifndef POTION_HPP
#define POTION_HPP

class Potion
{
private:
    int healingAmount;

public:
    Potion();
    int use() const;
};

#endif