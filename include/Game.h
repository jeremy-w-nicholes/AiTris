#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Block.h"
#include "AiGame.h"



class AiGame;
class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void DropBlock();
    bool gameOver;
    int score;
    void updateTimer();
    void updateGame();
    bool playerWins();
    int timerSeconds;
    int level;
    int comboCount;

    static constexpr int BASE_SPEED = 1000;
    static constexpr int SPEED_INCREMENT = 50;

    int calculateDropInterval(int level);

private:
    AiGame* aigame;

    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints, int dropPoints,
                     int comboMultiplier, bool isPerfectClear);

    double lastUpdateTime{0.0};
    std::vector<Block> blocks;
    std::vector<Block> GetAllBlocks();
    std::chrono::steady_clock::time_point startTime;

    bool IsBlockOutside();
    bool BlockFits();

    Grid grid;
    Block GetRandomBlock();
    Block currentBlock;
    Block nextBlock;
};

#endif