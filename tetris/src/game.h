#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
public:
    Game();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block> regenerateBlockList();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void LockBlock();    
    bool BlockFits();
    bool gameOver;
    int score;
private:
    std::vector<Block> blocks;
    void RotateBlock();
    void Reset();
    void UpdateScore(int linesCompleted,int numDown);
    Block currentBlock;
    Block nextBlock;
    bool isBlockOutside();
};