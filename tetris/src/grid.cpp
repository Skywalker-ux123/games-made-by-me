#include "grid.h"
#include <iostream>
#include "colors.h"


Grid::Grid(){
    numbRows = 20;
    numbColumns = 10;
    cellSize = 60;
    Initialize();
    colours = GetCellColours(); 
}

void Grid::Initialize(){
    for(int row=0; row < numbRows; row++){
        for(int col=0; col < numbColumns; col++){
            grid[row][col] = 0;
        }
    }
}

//row --> x coords ,col --> y coords
void Grid::Draw(){
    for(int row=0; row < numbRows; row++){
        for(int col=0; col < numbColumns; col++){
            int cellValue = grid[row][col];
            DrawRectangle(col*cellSize+21/*offset*/, row*cellSize+21, cellSize-1, cellSize-1, colours[cellValue]);
        }
    }
}

bool Grid::isCellOutside(int row, int col){
    if(row >= 0 && row < numbRows && col >=0 && col < numbColumns){
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column){
    if(grid[row][column] == 0){
        return true;    
    }
    return false;
}

int Grid::clearFullRows()
{
    int completed = 0;
    for(int row = numbRows-1; row >=0; row--){
        if(isRowFull(row)){
            clearRow(row);
            completed++;
        }else if(completed > 0){
            MoveDownRows(row,completed);
        }
    }
    return completed;
}

bool Grid::isRowFull(int row){
    int count = 0;
    for(int col=0; col < numbColumns; col++){
        if(grid[row][col] != 0){
            count++;
        }
    }
    if(count == 10){
        return true;
    }
    return false;
}

void Grid::clearRow(int row){
    for(int col=0; col < numbColumns; col++){
        grid[row][col] = 0;
    }
}

void Grid::MoveDownRows(int row, int numRows)
{
    for(int col=0; col < numbColumns; col++){
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
