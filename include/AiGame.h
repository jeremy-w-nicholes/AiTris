#ifndef AIGAME_H
#define AIGAME_H

#include "AiGrid.h"
#include "Game.h"
#include <chrono>
#include <iostream>
#include "Block.h"
#include <raylib.h>

class Game;
class AiGame
{
public:
    AiGame();

    void Draw();

    void updateGame();
    void MoveBlockDown();
    void Reset();

    bool gameOver{false};
    bool aiWins() ;

    static constexpr int BASE_SPEED = 1000;
    static constexpr int SPEED_INCREMENT = 50;

    int calculateDropInterval(int level);

    int score;
    int level;

private:
    Game* game;

    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void DropBlock();
    void LockBlock();

    void UpdateScore(int linesCleared, int moveDownPoints, int dropPoints,
                     int comboMultiplier, bool isPerfectClear);

    int comboCount;
    double lastUpdateTime{0.0};
    std::vector<Block> blocks;
    std::vector<Block> GetAllBlocks();
    std::chrono::steady_clock::time_point startTime;

    bool IsBlockOutside();
    bool BlockFits();

    AiGrid aigrid;
    Block GetRandomBlock();
    Block currentBlock;
    Block nextBlock;
};

#endif // AIGAME_H
