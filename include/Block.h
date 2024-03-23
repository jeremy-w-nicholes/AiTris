#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void RotateBLock();
    void UndoRotate();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};

#endif // BLOCK_H