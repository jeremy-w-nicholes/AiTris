#include <raylib.h>
#include "../include/Game.h"
#include "../include/AiGame.h"
#include "../include/Colors.h"
#include <iostream>


double lastUpdateTime = 0;

bool EventTriggered(double& lastUpdateTime, double interval, int level, int baseSpeed, int speedIncrement) {
    double currentTime = GetTime();
    double timeElapsed = (currentTime - lastUpdateTime) * 1000;
    int dropInterval = baseSpeed - (level - 1) * speedIncrement; 

    if (timeElapsed >= dropInterval) {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

int main() {
    InitWindow(1000, 620, "AiTris");
    SetTargetFPS(60);
    Font font = LoadFontEx("/workspaces/AiTris/assets/fonts/monogram.ttf", 64, 0, 0);

    srand(time(NULL));
    Game* game = new Game();
    AiGame* aigame = new AiGame();

    double aiLastUpdateTime = 0;

    while (!WindowShouldClose()) {
        game->HandleInput();
        game->updateGame();

        aigame->updateGame();

        if (EventTriggered(aiLastUpdateTime, 0.2, aigame->level, AiGame::BASE_SPEED, AiGame::SPEED_INCREMENT)) {
            aigame->MoveBlockDown();
        }

        game->updateTimer();        
        BeginDrawing();
        ClearBackground(WHITE);
        char timerText[10];
        sprintf(timerText, "%02d:%02d", game->timerSeconds / 60, game->timerSeconds % 60);
        DrawTextEx(font, "Time", {445, 15}, 38, 2, BLACK);
        DrawRectangleRounded({400, 55, 170, 60}, 0.3, 6, darkGrey);
        DrawTextEx(font, timerText, {400 + (170 - MeasureTextEx(font, timerText, 38, 2).x) / 2, 65}, 38, 2, WHITE);

        DrawTextEx(font, "Next", {370, 175}, 38, 2, BLACK);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, darkGrey);

        DrawTextEx(font, "Score", {365, 400}, 38, 2, BLACK);
        DrawRectangleRounded({320, 440, 170, 60}, 0.3, 6, darkGrey);
        char scoreText[10];
        sprintf(scoreText, "%d", game->score);
        DrawTextEx(font, scoreText, {320 + (170 - MeasureTextEx(font, scoreText, 38, 2).x) / 2, 450}, 38, 2, WHITE);

        // Formatting AI score text
        char aiScoreText[10];
        sprintf(aiScoreText, "%i", aigame->score);
        DrawTextEx(font, "AI Score", {515, 400}, 38, 2, BLACK); 
        DrawRectangleRounded({500, 440, 170, 60}, 0.3, 6, darkGrey);
        DrawTextEx(font, aiScoreText, {500 + (170 - MeasureTextEx(font, aiScoreText, 38, 2).x) / 2, 450}, 38, 2, WHITE);

        DrawTextEx(font, "AI Next", {515, 175}, 38, 2, BLACK);
        DrawRectangleRounded({500, 215, 170, 180}, 0.3, 6, darkGrey);

        // Assuming game is a pointer to a Game object and playerWins is a member function of Game
bool winStatus = game->playerWins();

if (winStatus) {  // Check if winStatus has a value
    if (winStatus == true) {
        // Player wins
        DrawTextEx(font, "You Win", {420, 125}, 38, 2, GREEN);
    } else {
        // Player loses
        DrawTextEx(font, "You Lose", {420, 125}, 38, 2, RED);
    }
}

        

        game->Draw();
        aigame->Draw();
    
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

