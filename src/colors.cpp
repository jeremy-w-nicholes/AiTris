#include "../include/Colors.h"


const Color darkGrey = {75, 68, 68, 255};
const Color green = {0, 153, 51, 255};
const Color red = {255, 0, 0, 255};
const Color orange = {255, 172, 17, 189};
const Color yellow = {237, 234, 4, 255};
const Color purple = {120, 0, 163, 255};
const Color cyan = {0, 255, 255, 255};
const Color blue = {0, 0, 255, 255};
const Color lightBlue = {240, 235, 214, 255};
const Color darkBlue = {59, 126, 163, 255};

std::vector<Color> GetCellColors()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}