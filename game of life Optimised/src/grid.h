#pragma once
#include <vector>
#include <cstdint>
#include <raylib.h>
#include <random>


class Grid{
private:
public:
    Grid();
    int ROWS;
    int COLS;
    int cellSize;
    std::vector<uint8_t> currentGrid;
    std::vector<uint8_t> nextGrid;
    int countNeighbor(int x, int y);
    void simulation();
    void initialize();
    void empty();
    // void Draw();
    int index(int row,int col);
};