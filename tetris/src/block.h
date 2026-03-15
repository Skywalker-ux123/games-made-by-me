#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class  Block{
public:
    Block();
    void Draw();
    void Move(int row, int column);
    std::vector<Position> GetPosition();
    void Rotate();
    void UndoRotate();
    int id;
    void isOutside();
    std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colours;
    int rowOffset, colOffset;
};