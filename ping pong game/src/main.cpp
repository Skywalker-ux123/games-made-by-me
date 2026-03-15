#include <iostream>
#include <raylib.h>

using namespace std;

Color NCyan = Color{ 0, 255, 255, 255 };
Color DeepMagenta = Color{ 255, 0, 255, 255};
Color ElectricBlue = Color{ 0, 100, 255, 255 };
Color CyberGray = Color{ 40, 40, 50, 255 };


int playerScore = 0;
int cpuScore = 0;


class Ball{
public:
float x,y;
int speed_x, speed_y;
int radius;

void Draw(){
    DrawCircle(x,y,radius,NCyan);
}

void Update(){
    x += speed_x;
    y += speed_y;

    if(y + radius >= GetScreenHeight()-10 || y - radius <= 10){//downside of the ball for lower wall and upside of the ball for 
        speed_y *= -1;
    }
    if(x + radius >= GetScreenWidth()-10){//right side of the ball
        playerScore++;
        ResetBall();
    } 
    if(x - radius <= 10){//left side of tha ball
        cpuScore++;
        ResetBall();
    }
}

void ResetBall(){
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speedChoice[2] = {1,-1};//randomly assigned direction with same prior speed
    speed_x *= speedChoice[GetRandomValue(0,1)];
    speed_y *= speedChoice[GetRandomValue(0,1)];
}

};

class Paddle{

protected:
    void LimitMovement(){
        if(y <= 10){
            y = 10;
        }
        if(y >= GetScreenHeight()-10-height){
            y = GetScreenHeight()-10-height;
        }
    }
    
public:
    float x,y;
    int speedY,speedX=0;
    float width,height;

    void Draw(){
        DrawRectangle(x,y,width,height,NCyan);
    }

    void Update(){
        if(IsKeyDown(KEY_UP || KEY_W)){
            y -= speedY;
        }
        if(IsKeyDown(KEY_DOWN || KEY_S)){
            y += speedY;    
        }
        LimitMovement();
    }
};

class CpuPaddle : public Paddle{
public: 
    void Update(int ball_y){
        if(y + height/2 > ball_y){
            y -= speedY;
        }
        if(y + height/2 <= ball_y){
            y += speedY;
        }
        LimitMovement();
    }

};  

Ball ball;
Paddle paddle1;
CpuPaddle cpu;

int main(){

    const int screen_width = 1920;
    const int screen_height = 1080;
    
    InitWindow(screen_width,screen_height,"Pong game!");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 9, ball.speed_y = 9;

    paddle1.width = 20;
    paddle1.height = 200;
    paddle1.x = screen_width-1910;
    paddle1.y = (screen_height/2)-100;
    paddle1.speedY = 5;

    cpu.width = 20;
    cpu.height = 200;
    cpu.x = screen_width-30;
    cpu.y = (screen_height/2)-100;
    cpu.speedY = 7;

    while(WindowShouldClose() == false){
        BeginDrawing();
        
        //Updating
        ClearBackground(CyberGray);
        ball.Update();
        paddle1.Update();
        cpu.Update(ball.y);

        //Checking collisions
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{paddle1.x, paddle1.y,paddle1.width,paddle1.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x, cpu.y,cpu.width,cpu.height})){
            ball.speed_x *= -1;
        }

        //Drawing
        DrawLine(screen_width/2, 10, screen_width/2, screen_height-10, NCyan);
        DrawLine(10,10,screen_width-10,10,NCyan);
        DrawLine(10,screen_height-10,screen_width-10,screen_height-10,NCyan);
        DrawLine(10,10,10,screen_height-10,NCyan);
        DrawLine(screen_width-10,10,screen_width-10,screen_height-10,NCyan );
        ball.Draw();
        paddle1.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i",playerScore),(screen_width/4)+10,(screen_height/4)+10,200,NCyan);
        DrawText(TextFormat("%i",cpuScore),3*(screen_width/4) - 10,(screen_height/4)+10,200,NCyan);
        

        EndDrawing();

    }

    CloseWindow();
    return 0;
}