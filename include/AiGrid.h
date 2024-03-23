#ifndef AIGRID_H
#define AIGRID_H

#include <vector>
#include <raylib.h>  // Make sure this path is correct based on your project's structure
class Game;
class AiGrid
{
public:
    AiGrid();
    int grid[20][10];
    void Initialize();
    void Draw();

    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    bool IsGridEmpty();
    
private:
    

    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);

    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};

#endif // AIGRID_H
