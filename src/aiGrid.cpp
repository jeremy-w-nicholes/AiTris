#include "../include/AiGrid.h"
#include "../include/Colors.h" // Update this path based on your project's structure

AiGrid::AiGrid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;

    Initialize();

    colors = GetCellColors(); 
}

void AiGrid::Initialize() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void AiGrid::Draw()
{
    int playerGridWidth = numCols * cellSize;
    int horizontalOffset = 390;
    int verticalOffset = 10;
    int xOffset = playerGridWidth + horizontalOffset; 
    int yOffset = verticalOffset;

    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            DrawRectangle(xOffset + column * cellSize, yOffset + row * cellSize, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}



bool AiGrid::IsCellOutside(int row, int column){
    if (row < 0 || row >= numRows || column < 0 || column >= numCols)
    {
        return true;
    }
    return false;
}

bool AiGrid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

bool AiGrid::IsGridEmpty(){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] != 0) 
            {
                return false;
            }
        }
    }
    return true;
}

int AiGrid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) 
    {
        if (IsRowFull(row)) 
        {
            ClearRow(row);
            completed++;
        } 
        else if (completed > 0) 
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}



bool AiGrid::IsRowFull(int row){
    for (int column = 0; column < numCols; ++column) 
    {
        if (grid[row][column] == 0) 
        {
            return false;
        }
    }
    return true;
}

void AiGrid::ClearRow(int row) 
{
    for (int column = 0; column < numCols; ++column) 
    {
        grid[row][column] = 0;
    }
}

void AiGrid::MoveRowDown(int row, int numRows) 
{
    for (int column = 0; column < numCols; ++column) 
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}


