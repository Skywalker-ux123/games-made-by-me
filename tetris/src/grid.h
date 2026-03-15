#pragma once 
#include <vector>
#include <map>
#include <raylib.h>

class Grid{
public:
    Grid();
    void Initialize();
    int grid[20][10];
    void Draw();
    bool isCellOutside(int row, int col);
    bool IsCellEmpty(int row, int column);
    int clearFullRows();
    

private:
    bool isRowFull(int row);
    void clearRow(int row);
    void MoveDownRows(int row, int numRows);
    int numbRows;
    int numbColumns;
    int cellSize;
    std::vector<Color> colours;
};