#include <raylib.h>
#include <iostream>
#include <vector>

Color neonCyan = { 0, 255, 255, 255 }; 
Color gridBackground = { 10, 15, 20, 255 };
Color gridLines = { 40, 50, 60, 255 };
int currentGrid[108][192];
int nextGrid[108][192];
int cellSize = 10;
std::vector<Color> Colours = {gridBackground, neonCyan};

void initialize(int grid[108][192]){
    for(int row=0;row<108;row++){
        for(int col=0;col<192;col++){
            grid[row][col] = GetRandomValue(0,1);
        }
    }
} 

void Simulation(int grid[108][192],int grid2[108][192]){
    for(int row=1; row<108; row++){
        for(int col=1; col<192; col++){
            int count = 0;
            for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(grid[row+i][col+j] == 1){
                        count += grid[row+i][col+j];
                    }
                }
            }
            count -= grid[row][col];

            if(count < 2){
                grid2[row][col] = 0;
            }else if(count > 2 && count < 4){
                grid2[row][col] = 1;
            }else{
                grid2[row][col] = 0;
            }
        }
    }
}

void Draw(int grid[108][192]){
    
    for(int row=0; row<108; row++){
        for(int col=0; col<192; col++){
            DrawRectangle(col*cellSize+1,row*cellSize+1,cellSize-1,cellSize-1,Colours[grid[row][col]]);
        }
    }
    
}

void SwapGrid(int grid1[108][192],int grid2[108][192]){
    for(int row=0; row<108; row++){
        for(int col=0; col<192; col++){
            grid1[row][col] = grid2[row][col];
        }
    }
}


int main(){

    
    InitWindow(1920,1080,"Conway's Game of LIFE");
    SetTargetFPS(12);
    initialize(currentGrid);

    while(WindowShouldClose() == false){
      
        BeginDrawing();
        ClearBackground(gridLines);
        Simulation(currentGrid,nextGrid);
        Draw(currentGrid);
        SwapGrid(currentGrid,nextGrid);
        EndDrawing();

    }


    CloseWindow();
    return 0;
}



