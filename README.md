# RPG Game

A simple C++ terminal RPG arena game. Fight various enemies and bosses, collect weapons and potions, and manage your inventory. The game supports saving/loading progress and features colored output for better readability.

## Features

- Turn-based combat with random enemies and bosses
- Multiple weapon and potion types (with special effects)
- Inventory management (choose and use weapons/potions)
- Leveling up and experience system
- Save and load your game progress
- Colorful terminal UI and in-game help

## Controls

- **1** – Attack enemy
- **2** – Use potion
- **3** – Run away (ends the game)
- **4** – Show inventory
- **5** – Change active weapon
- **6** – Save game
- **7** – Show help

## Build & Run

```sh
mkdir build
cd build
cmake ..
make
./rpg_game
```

## Save/Load

- On game start, choose **1** for a new game or **2** to continue from your last save.
- You can save your progress anytime during battle by choosing option **6**.

## Requirements

- C++17 compiler
- CMake

---

Enjoy the game!
