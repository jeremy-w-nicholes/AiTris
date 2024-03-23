#ifndef GRID_H
#define GRID_H

#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    int grid[20][10];
    void Initialize();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    bool IsGridEmpty() ;
    

private:
    bool IsRowFull(int row) ;
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);

    
    int numRows{20};
    int numCols{10};
    int cellSize{0};
    std::vector<Color> colors;
};

#endif // GRID_H