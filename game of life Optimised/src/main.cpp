#include <iostream>
#include <raylib.h>
#include "grid.h"
#include <vector>
#include <algorithm>

Color gridColor = {40, 40, 40, 255};
Color gridBackground = { 10, 15, 20, 255 };
Color neonCyan = { 0, 255, 255, 255 };

Grid grid = Grid();
bool isRunning = true;

int main(){

    int FPS = 12;
    int screenWidth = 1920, screenHeight = 1080;
    InitWindow(screenWidth,screenHeight,"Conways game of life optimised");
    SetTargetFPS(FPS);
    grid.empty();
    bool isRunning = false;
    Camera2D camera = {0};
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){0.0f,0.0f};
    camera.rotation = 0;
    camera.zoom = 1.0f;

    while(!WindowShouldClose()){
        
        float wheel = GetMouseWheelMove();
        camera.zoom += wheel*0.1f;
        if(camera.zoom < 0.3f) camera.zoom = 0.3f;
        
        
        static Vector2 prevMouse = {0};


        if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
            Vector2 delta = { GetMouseX() - prevMouse.x, GetMouseY() - prevMouse.y };

            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;

            float worldWidth = (float)(grid.COLS*grid.cellSize)/2;
            float worldHeight = (float)(grid.ROWS*grid.cellSize)/2;
            float halfWidth = GetScreenWidth()/2;
            float halfHeight = GetScreenHeight()/2;

            if(camera.target.x < 0){
                camera.target.x = 0;
            }
            if(camera.target.y < 0){
                camera.target.y = 0;
            }
            if(camera.target.x >= worldWidth - halfWidth){
                camera.target.x = worldWidth - halfWidth;
            }
            if(camera.target.y >= worldHeight - halfHeight){
                camera.target.y = worldHeight - halfHeight;
            }
            


        }

        prevMouse = (Vector2){(float)GetMouseX(), (float)GetMouseY()};

        if (!isRunning && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
            int col = (int)(mouseWorld.x / grid.cellSize);
            int row = (int)(mouseWorld.y / grid.cellSize);

            if (row >= 0 && row < grid.ROWS && col >= 0 && col < grid.COLS) {
                int index = grid.index(row,col);
                grid.currentGrid[index] = !grid.currentGrid[index];
            }
        }

        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }

        if(IsKeyPressed(KEY_D)){
            FPS += 6;
            SetTargetFPS(FPS);
        }

        if(IsKeyPressed(KEY_A)){
            FPS -= 6;
            SetTargetFPS(FPS);
        }

        if(IsKeyPressed(KEY_Y)){
            grid.empty();
        }

        if(IsKeyPressed(KEY_SPACE)){
            isRunning = !isRunning;
        }

        if(IsKeyPressed(KEY_R)){
            grid.initialize();
        }

        if(isRunning){
            grid.simulation();
        }

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(gridBackground);
        float sWidth = (float)GetScreenWidth();
        float sHeight = (float)GetScreenHeight();
        Vector2 worldTopLeft = GetScreenToWorld2D({0,0},camera);
        Vector2 worldBottomRight = GetScreenToWorld2D({sWidth, sHeight},camera);

        int startRow = worldTopLeft.y/grid.cellSize;
        int endRow = worldBottomRight.y/grid.cellSize;

        int startCol = worldTopLeft.x/grid.cellSize;
        int endCol = worldBottomRight.x/grid.cellSize;

        startRow = std::max(0,startRow);
        endRow = std::min(grid.ROWS-1,endRow);
        startCol = std::max(0,startCol);
        endCol = std::min(grid.COLS-1,endCol);
        
        for(int row = startRow; row < endRow; row++){
            for(int col = startCol; col < endCol; col++){
                if(grid.currentGrid[grid.index(row,col)] == 1){
                    DrawRectangle(col*grid.cellSize+1,row*grid.cellSize+1,grid.cellSize-1,grid.cellSize-1,neonCyan);
                }
            }
        }

        // grid.Draw();
        EndMode2D();
        EndDrawing();
    }

    return 0;

}