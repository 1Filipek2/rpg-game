#include "game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Golem : public Enemy
{
public:
    Golem() : Enemy("Golem", 80 + rand() % 11, 8 + rand() % 4) {}
};
class Drake : public Enemy
{
public:
    Drake() : Enemy("Drak", 90 + rand() % 11, 10 + rand() % 4) {}
};
class Minotaur : public Enemy
{
public:
    Minotaur() : Enemy("Minotaurus", 70 + rand() % 11, 6 + rand() % 4) {}
};

Game::Game() {}

void Game::start()
{
    srand(time(nullptr));

    while (player.isAlive())
    {
        int e = rand() % 3;
        if (e == 0)
            enemy = std::make_unique<Minotaur>();
        else if (e == 1)
            enemy = std::make_unique<Golem>();
        else
            enemy = std::make_unique<Drake>();

        std::cout << "\nVitaj v RPG Aréne!\n";
        player.printStatus();
        std::cout << "Nepriateľ: " << enemy->getName() << " (HP: " << enemy->getHP() << ")\n\n";

        while (player.isAlive() && enemy->isAlive())
        {
            std::cout << "1. Útok\n2. Použi potion\n3. Útek\nVoľba: ";
            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                player.attack(*enemy);
                std::cout << "Nepriateľove HP: " << enemy->getHP() << "\n";

                if (enemy->isAlive())
                {
                    enemy->attack(player);
                    std::cout << "Tvoje HP: " << player.getHP() << "\n\n";
                }
            }
            else if (choice == 2)
            {
                player.heal();
            }
            else if (choice == 3)
            {
                std::cout << "Utiekol si z boja!\n";
                return;
            }
            else
            {
                std::cout << "Neplatná voľba.\n";
            }
        }

        if (player.isAlive())
        {
            std::cout << "\nPorazil si " << enemy->getName() << "!\n";
            player.gainXP(50);

            int reward = rand() % 2;
            if (reward == 0)
            {
                player.getInventory().addPotion(Potion());
                std::cout << "Získal si potion!\n";
            }
            else
            {
                int dmg = 10 + rand() % 11;
                std::string names[] = {"Sekera", "Kopija", "Kladivo"};
                std::string wname = names[rand() % 3];
                player.getInventory().addWeapon(std::make_unique<Weapon>(wname, dmg));
                std::cout << "Získal si zbraň: " << wname << " (" << dmg << " dmg)!\n";
            }
        }
        else
        {
            std::cout << "\nBol si porazený.\n";
        }
    }
}