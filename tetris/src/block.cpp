#include "block.h"

Block::Block(){
    cellSize = 60;
    rotationState = 0;
    colours = GetCellColours();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw(){
    std::vector<Position> tiles = GetPosition();
    for(Position item: tiles){
        DrawRectangle(item.col*cellSize + 21, item.row*cellSize + 21, cellSize - 1, cellSize - 1, colours[id]);        
    }
}

void Block::Move(int row, int column){
    rowOffset += row;
    colOffset += column;
}

std::vector<Position> Block::GetPosition(){
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);//og coords + relative coords
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate(){
    rotationState++;
    if(rotationState == (int)cells.size()){
        rotationState = 0;
    }
}

void Block::UndoRotate(){
    rotationState--;
    if(rotationState == -1){
        rotationState = (int)cells.size() - 1;
    }
}