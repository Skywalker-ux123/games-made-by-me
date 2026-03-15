#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

Color GRID_LINE = { 40, 50, 80, 255 };
Color BORDER = { 0, 255, 255, 180 };
Color UI_TEXT = { 0, 255, 200, 255 };
Color UI_DIM  = { 0, 180, 140, 255 };
Color GLOW_CYAN = { 0, 255, 255, 120 };
Color GLOW_PURPLE = { 180, 0, 255, 120 };

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime > interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(){

    Font font = LoadFontEx("font/xyz.ttf", 64, 0,0);
    Color BG_GRID = { 25, 30, 45, 255 }; 
    InitWindow(1000,1240,"Tetris"); 
    SetTargetFPS(60);
    Game game = Game();
    
    while(!WindowShouldClose()){
        
        
        game.HandleInput();
        if(eventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(BG_GRID);
        //UI
        DrawTextEx(font,"Score", {765,25}, 38, 2,UI_TEXT);
         
        if(game.gameOver){
            DrawTextEx(font,"GAME OVER", {720,950}, 38, 2,UI_TEXT);
        }
        DrawRectangleRounded({735,65,170,60},0.3,6,GRID_LINE);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        DrawTextEx(font,scoreText, {810,75}, 38, 2,UI_TEXT);
        game.Draw();
        EndDrawing();

    }


    CloseWindow();
    return 0;
}


