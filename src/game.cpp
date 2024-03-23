#include "../include/Game.h"
#include "../include/AiGame.h"
#include "blocks.cpp"

#include <random>

Game::Game() 
    : gameOver(false),
      score(0),
      timerSeconds(120),
      level(1),
      comboCount(0),
      lastUpdateTime(GetTime()),
      blocks(GetAllBlocks()),
      startTime(std::chrono::steady_clock::now()),
      grid(),
      currentBlock(GetRandomBlock()),
      nextBlock(GetRandomBlock()) {

      }

bool Game::playerWins() {
    if (!gameOver && !aigame->gameOver) {
        
        return false;
    }

    bool condition1 = !gameOver && aigame->gameOver;
    bool condition2 = timerSeconds == 0 && score > aigame->score;
    return condition1 || condition2;
}

bool AiGame::aiWins() {
    if (!gameOver && !game->gameOver) {
        return false;
    }

    bool condition1 = !gameOver && game->gameOver;
    bool condition2 = game->timerSeconds == 0 && score > game->score;
    return condition1 || condition2;
}



Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
    
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id) {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}


void Game::updateTimer() {
    if (gameOver || aigame->gameOver) return;

    auto now = std::chrono::steady_clock::now();
    if (now - startTime >= std::chrono::seconds{1}) {
        timerSeconds--;
        startTime = now;
    }

    if (timerSeconds <= 0) gameOver = true;
}



void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0) {
        timerSeconds = 120;
        Game::Reset();
        aigame->Reset();
    }
    switch (keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1, 0, 0, false);
            break;
        case KEY_UP:
            RotateBlock();
            break;
        case KEY_SPACE:
            DropBlock();
            UpdateScore(0, 0, 1, 0, false);
            break;
    }
}

void Game::MoveBlockLeft() {
    if (!gameOver) {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {

        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::DropBlock() {

    while (!gameOver) {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(-1, 0);
            break;
        }
    }
    LockBlock();
}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    if (!gameOver) {
        currentBlock.RotateBLock();
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.UndoRotate();
        }
    }
}

void Game::LockBlock() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    // Check if the new current block fits in the starting position.
    if (!BlockFits()) {
        gameOver = true;  // Set the game over condition to true.
        aigame->gameOver = true;  // Assuming you want the AI game to end as well when the player tops out.
    }

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0) {
        UpdateScore(rowsCleared, 0, 0, 1, grid.IsGridEmpty());
        comboCount++; 
    } else {
        comboCount = 0;
    }
}


bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (!grid.IsCellEmpty(item.row, item.column)) {
            return false;
        }
    }
    return true;
}

void Game::Reset() {
    score = 0;
    comboCount = 0;
    level = 1;
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints, int dropPoints, int comboMultiplier, bool isPerfectClear) {
    int baseScore = 0;

    switch (linesCleared)
    {
    case 1:
        baseScore = isPerfectClear ? 800 : 100;
        break;
    case 2:
        baseScore = isPerfectClear ? 1200 : 300;
        break;
    case 3:
        baseScore = isPerfectClear ? 1800 : 500;
        break;
    case 4:
        baseScore = isPerfectClear ? 2000 : 800;
        break;
    default:
        break;
    }

    int comboScore = comboCount > 0 ? (50 * comboCount * level) : 0;
    baseScore *= level;
    comboScore *= level;
    int moveDownScore = moveDownPoints * level;
    int dropScore = dropPoints * 10 * level; 

    score += baseScore + comboScore + moveDownScore + dropScore;
}

int Game::calculateDropInterval(int level) {
    int interval = BASE_SPEED - (level - 1) * SPEED_INCREMENT;
    return std::max(interval, 100); 
}

void Game::updateGame() {
    if (aigame->gameOver && aigame->gameOver) {
        return;
    }

    double currentTime = GetTime();
    double timeElapsed = (currentTime - lastUpdateTime) * 1000;

    if (timeElapsed >= calculateDropInterval(level)) {
        MoveBlockDown();
        lastUpdateTime = currentTime;
    }
}






//AIGAME

AiGame::AiGame() 
    : gameOver(false),
      score(),
      level(),
      comboCount(0),
      lastUpdateTime(GetTime()), 
      blocks(GetAllBlocks()), 
      aigrid(), 
      currentBlock(GetRandomBlock()),
      nextBlock(GetRandomBlock()) {
        
    aigrid = AiGrid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    level = 1;
}

Block AiGame::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> AiGame::GetAllBlocks() 
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void AiGame::Draw() {

    int aiCurrentBlockX = 690;
    int aiCurrentBlockY = 10;
    
    aigrid.Draw();
    currentBlock.Draw(aiCurrentBlockX, aiCurrentBlockY);;
    switch (nextBlock.id) {
        case 3:
            nextBlock.Draw(438, 290);
            break;
        case 4:
            nextBlock.Draw(438, 280);
            break;
        default:
            nextBlock.Draw(458, 270);
            break;
    }
}


void AiGame::MoveBlockLeft() {
    if (!gameOver) {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, 1);
        }
    }
}

void AiGame::MoveBlockRight() {
    if (!gameOver) {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(0, -1);
        }
    }
}

void AiGame::MoveBlockDown() {
    if (!gameOver) {

        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void AiGame::DropBlock() {

    while (!gameOver) {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.Move(-1, 0);
            break;
        }
    }
    LockBlock();
}

bool AiGame::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (aigrid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void AiGame::RotateBlock() {
    if (!gameOver) {
        currentBlock.RotateBLock();
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock.UndoRotate();
        }
    }
}

void AiGame::LockBlock() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        aigrid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    // Check if the new current block fits in the starting position.
    if (!BlockFits()) {
        gameOver = true;  // Set the game over condition for AI to true.
        if (gameOver) {
            game->gameOver = true;  // Also set the player's game to over if the AI tops out, if necessary.
        }
    }

    int rowsCleared = aigrid.ClearFullRows();
    if (rowsCleared > 0) {
        UpdateScore(rowsCleared, 0, 0, 1, aigrid.IsGridEmpty());
        comboCount++; 
    } else {
        comboCount = 0;
    }
}


bool AiGame::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (!aigrid.IsCellEmpty(item.row, item.column)) {
            return false;
        }
    }
    return true;
}

void AiGame::Reset() {
    score = 0;
    comboCount = 0;
    level = 1;
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    
}

void AiGame::UpdateScore(int linesCleared, int moveDownPoints, int dropPoints, int comboMultiplier, bool isPerfectClear) {
    int baseScore = 0;

    switch (linesCleared)
    {
    case 1:
        baseScore = isPerfectClear ? 800 : 100;
        break;
    case 2:
        baseScore = isPerfectClear ? 1200 : 300;
        break;
    case 3:
        baseScore = isPerfectClear ? 1800 : 500;
        break;
    case 4:
        baseScore = isPerfectClear ? 2000 : 800;
        break;
    default:
        break;
    }

    int comboScore = comboCount > 0 ? (50 * comboCount * level) : 0;
    baseScore *= level;
    comboScore *= level;
    int moveDownScore = moveDownPoints * level;
    int dropScore = dropPoints * 10 * level; 

    score += baseScore + comboScore + moveDownScore + dropScore;
}

int AiGame::calculateDropInterval(int level) {
    int interval = BASE_SPEED - (level - 1) * SPEED_INCREMENT;
    return std::max(interval, 100); 
}

void AiGame::updateGame() {
    srand(static_cast<unsigned int>(time(0)));
    if ((gameOver && gameOver) || (game->gameOver && game->gameOver)) {
        return;
    }

    double currentTime = GetTime();
    double timeElapsed = (currentTime - lastUpdateTime) * 1000;

    if (timeElapsed >= calculateDropInterval(level)) {
        MoveBlockDown();
        //AI_Agent bestAgent = getBestAgentFromCurrentGeneration();
        int action = rand() % 10; // Generate a random number between 0 and 9

        if (action == 5 || action == 6) { // 20% chance to drop the block instantly
            DropBlock();
        } else if (action == 7) { // 10% chance to move left
            MoveBlockLeft();
        } else if (action == 8) { // 10% chance to move right
            MoveBlockRight();
        } else if (action == 9) { // 10% chance to rotate the block
            RotateBlock();
        }

        lastUpdateTime = currentTime;
        std::cout << "AI action: " << action << std::endl; // Debug output

    }
}




