#include "game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "colors.hpp"

class Golem : public Enemy
{
public:
    Golem() : Enemy("Golem", 80 + rand() % 11, 8 + rand() % 4) {}
};
class Drake : public Enemy
{
public:
    Drake() : Enemy("Drake", 90 + rand() % 11, 10 + rand() % 4) {}
};
class Minotaur : public Enemy
{
public:
    Minotaur() : Enemy("Minotaur", 70 + rand() % 11, 6 + rand() % 4) {}
};
class Boss : public Enemy
{
public:
    Boss() : Enemy("Hydra", 150 + rand() % 31, 15 + rand() % 6) {}
    void specialAbility(Player &player) override
    {
        std::cout << COLOR_MAGENTA << name << " used special attack: Poison Breath! You lose 10 extra HP!\n"
                  << COLOR_RESET;
        player.takeDamage(10);
    }
};

Game::Game() {}

bool Game::saveGame() const
{
    std::ofstream file("savegame.txt");
    if (!file)
        return false;
    file << player.getHP() << " " << player.getXP() << " " << player.getLevel() << "\n";
    file << player.getWeapon()->getName() << " " << player.getWeapon()->getDamage() << " " << static_cast<int>(player.getWeapon()->getEffect()) << "\n";
    const auto &potions = player.getInventory().getPotions();
    file << potions.size() << "\n";
    for (const auto &p : potions)
        file << static_cast<int>(p.getType()) << "\n";
    const auto &weapons = player.getInventory().getWeapons();
    file << weapons.size() << "\n";
    for (const auto &w : weapons)
        file << w->getName() << " " << w->getDamage() << " " << static_cast<int>(w->getEffect()) << "\n";
    return true;
}

bool Game::loadGame()
{
    std::ifstream file("savegame.txt");
    if (!file)
        return false;
    int hp, xp, level;
    file >> hp >> xp >> level;
    player.setHP(hp);
    player.setXP(xp);
    player.setLevel(level);

    std::string wname;
    int wdamage, weffect;
    file >> wname >> wdamage >> weffect;
    player.setWeapon(std::make_unique<Weapon>(wname, wdamage, static_cast<WeaponEffect>(weffect)));

    size_t potionCount;
    file >> potionCount;
    player.getInventory().clearPotions();
    for (size_t i = 0; i < potionCount; ++i)
    {
        int ptype;
        file >> ptype;
        player.getInventory().addPotion(Potion(static_cast<PotionType>(ptype)));
    }

    size_t weaponCount;
    file >> weaponCount;
    player.getInventory().clearWeapons();
    for (size_t i = 0; i < weaponCount; ++i)
    {
        std::string name;
        int dmg, effect;
        file >> name >> dmg >> effect;
        player.getInventory().addWeapon(std::make_unique<Weapon>(name, dmg, static_cast<WeaponEffect>(effect)));
    }

    return true;
}

void Game::start()
{
    srand(time(nullptr));
    bool firstFight = true;

    std::cout << COLOR_CYAN << "1. New Game\n2. Continue\nChoice: " << COLOR_RESET;
    int startChoice;
    std::cin >> startChoice;
    if (startChoice == 2)
    {
        if (!loadGame())
        {
            std::cout << COLOR_RED << "Loading failed, starting a new game.\n"
                      << COLOR_RESET;
        }
    }

    while (player.isAlive())
    {
        int e = rand() % 4;
        if (e == 0)
            enemy = std::make_unique<Minotaur>();
        else if (e == 1)
            enemy = std::make_unique<Golem>();
        else if (e == 2)
            enemy = std::make_unique<Drake>();
        else
            enemy = std::make_unique<Boss>();

        bool isBoss = dynamic_cast<Boss *>(enemy.get()) != nullptr;

        if (firstFight)
        {
            std::cout << COLOR_CYAN << "\nWelcome to the RPG Arena!\n"
                      << COLOR_RESET;
            firstFight = false;
        }
        else if (isBoss)
        {
            std::cout << COLOR_RED << "\n!!! BOSS FIGHT !!!\n"
                      << COLOR_RESET;
        }
        else
        {
            std::cout << COLOR_YELLOW << "\nYou proceed to the next battle...\n"
                      << COLOR_RESET;
        }

        if (isBoss)
        {
            std::cout << COLOR_RED << "You encounter the boss: " << enemy->getName() << " (HP: " << enemy->getHP() << ")\n\n"
                      << COLOR_RESET;
        }
        else
        {
            std::cout << COLOR_YELLOW << "Enemy: " << enemy->getName() << " (HP: " << enemy->getHP() << ")\n\n"
                      << COLOR_RESET;
        }
        player.printStatus();

        while (player.isAlive() && enemy->isAlive())
        {
            std::cout << COLOR_CYAN
                      << "1. Attack\n2. Use potion\n3. Run away\n4. Inventory\n5. Change weapon\n6. Save game\n7. Help\nChoice: "
                      << COLOR_RESET;
            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                player.attack(*enemy);
                std::cout << COLOR_YELLOW << "Enemy HP: " << enemy->getHP() << COLOR_RESET << "\n";

                if (enemy->isAlive())
                {
                    enemy->attack(player);
                    if (isBoss && (rand() % 100) < 30)
                    {
                        enemy->specialAbility(player);
                    }
                    std::cout << COLOR_CYAN << "Your HP: " << player.getHP() << "\n\n"
                              << COLOR_RESET;
                }
            }
            else if (choice == 2)
            {
                player.heal();
            }
            else if (choice == 3)
            {
                std::cout << COLOR_MAGENTA << "You ran away from the battle!\n"
                          << COLOR_RESET;
                return;
            }
            else if (choice == 4)
            {
                player.getInventory().printInventory();
            }
            else if (choice == 5)
            {
                player.chooseWeapon();
            }
            else if (choice == 6)
            {
                if (saveGame())
                    std::cout << COLOR_GREEN << "Game saved!\n"
                              << COLOR_RESET;
                else
                    std::cout << COLOR_RED << "Error while saving the game!\n"
                              << COLOR_RESET;
            }
            else if (choice == 7)
            {
                std::cout << COLOR_MAGENTA
                          << "Help:\n"
                          << "1 - Attack the enemy\n"
                          << "2 - Use a potion to heal\n"
                          << "3 - Run away (ends the game)\n"
                          << "4 - Show inventory\n"
                          << "5 - Change active weapon\n"
                          << "6 - Save the game\n"
                          << "7 - Show this help\n"
                          << COLOR_RESET;
            }
            else
            {
                std::cout << COLOR_RED << "Invalid choice.\n"
                          << COLOR_RESET;
            }
        }

        if (player.isAlive())
        {
            std::cout << COLOR_GREEN << "\nYou defeated " << enemy->getName() << "!\n"
                      << COLOR_RESET;
            player.gainXP(50);

            int reward = rand() % 2;
            if (reward == 0)
            {
                PotionType ptype = static_cast<PotionType>(rand() % 3);
                player.getInventory().addPotion(Potion(ptype));
                std::cout << COLOR_CYAN << "You received a " << Potion(ptype).getName() << "!\n"
                          << COLOR_RESET;
            }
            else
            {
                int dmg = 10 + rand() % 11;
                std::string names[] = {"Axe", "Spear", "Hammer"};
                std::string wname = names[rand() % 3];
                WeaponEffect effect = static_cast<WeaponEffect>(rand() % 3);
                player.getInventory().addWeapon(std::make_unique<Weapon>(wname, dmg, effect));
                std::cout << COLOR_CYAN << "You received a weapon: " << wname << " (" << dmg << " dmg)";
                if (effect == WeaponEffect::Critical)
                    std::cout << " [Critical]";
                else if (effect == WeaponEffect::Stun)
                    std::cout << " [Stun]";
                std::cout << "!\n"
                          << COLOR_RESET;
            }
        }
        else
        {
            std::cout << COLOR_RED << "\nYou have been defeated.\n"
                      << COLOR_RESET;
        }
    }
}