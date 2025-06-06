#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "enemy.hpp"
#include <memory>

class Game
{
private:
    Player player;
    std::unique_ptr<Enemy> enemy;

public:
    Game();
    void start();
    bool saveGame() const;
    bool loadGame();
};

#endif