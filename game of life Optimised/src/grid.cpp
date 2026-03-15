#include "grid.h"

// Color neonCyan = { 0, 255, 255, 255 }; 

Grid::Grid(){
    ROWS = 5000;
    COLS = 5000;
    cellSize = 10;
   
}

inline int Grid::index(int row,int col){
    return col * COLS + row;
}

int Grid::countNeighbor(int x, int y)
{
    int count = 0;
    for(int i=-1; i < 2; i++){
        for(int j=-1; j < 2; j++){
            int cell = index((x+j+COLS)%COLS,(y+i+ROWS)%ROWS);
            count += currentGrid[cell];
        }
    }
    
    count -= currentGrid[index(x,y)]; 
    
    return count;
}

void Grid::simulation(){
    for(int y=0; y < ROWS; y++){
        for(int x=0; x < COLS; x++){
            int ind = index(x, y);
            int neighbors = countNeighbor(x, y);

            if (currentGrid[ind] == 1)
            {
                if (neighbors < 2 || neighbors > 3)
                    nextGrid[ind] = 0;
                else
                    nextGrid[ind] = 1;
            }
            else
            {
                if (neighbors == 3)
                    nextGrid[ind] = 1;
                else
                    nextGrid[ind] = 0;
            }
        }
    }
    swap(currentGrid,nextGrid);
}

void Grid::initialize()
{   
    currentGrid.resize(ROWS * COLS);
    nextGrid.resize(ROWS * COLS);
    for(int i=0; i < ROWS*COLS; i++){
        currentGrid[i] = GetRandomValue(0,1);
    }
}

// void Grid::Draw(){
//     for(int row = 0; row < ROWS; row++){
//             for(int col = 0; col < COLS; col++){
//                 if(currentGrid[index(row,col)] == 1){
//                     DrawRectangle(col*cellSize,row*cellSize,cellSize,cellSize,neonCyan);
//                 }
//             }
//         }
// }

void Grid::empty()
{   
    currentGrid.resize(ROWS * COLS);
    nextGrid.resize(ROWS * COLS);
    for(int i=0; i < ROWS*COLS; i++){
        currentGrid[i] = 0;
    }
}
