#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = regenerateBlockList();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
        blocks = regenerateBlockList();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::regenerateBlockList(){
    return {Iblock(),Oblock(),Sblock(),Tblock(),Zblock(),Lblock(),Jblock()};
}

void Game::Draw(){
    grid.Draw();
    currentBlock.Draw();
}

//Controls 
void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
    switch(keyPressed){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0,1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
        default:
            break;
    }
}

void Game::MoveBlockLeft(){
    if(!gameOver){
        currentBlock.Move(0,-1);
        if(isBlockOutside() || !BlockFits()){
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight(){
    if(!gameOver){
        currentBlock.Move(0,1);
        if(isBlockOutside() || !BlockFits()){
            currentBlock.Move(0,-1);
        }
    }
    
}

void Game::MoveBlockDown(){
    if(!gameOver){
        currentBlock.Move(1,0);
        if(isBlockOutside() || !BlockFits()){
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
    
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetPosition();
    for(Position item: tiles){
        if(grid.isCellOutside(item.row,item.col)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if(!gameOver){
        currentBlock.Rotate();
        if(isBlockOutside() || !BlockFits()){
            currentBlock.UndoRotate();
        }
    }
    
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetPosition();
    for(Position item: tiles){
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(!BlockFits()){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.clearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetPosition();
    for(Position item: tiles){
        if(grid.IsCellEmpty(item.row,item.col) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    blocks = regenerateBlockList();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

//UI 
void Game::UpdateScore(int linesCompleted, int numDown)
{
    switch(linesCompleted){
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score +=500;
            break;
        default:
            break;
    }

    score += numDown;

}
