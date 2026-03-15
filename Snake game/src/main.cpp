#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

//declaring the grid and its size 
Color GrassGreen = {80, 200, 120, 255};
const int sWidth = 1920;
const int sHeight = 1080;
float cellSize = 30;
float cellHCount = 64;
float cellVCount = 36;
double lastUpdateTime = 0;
float offset = 100;

bool ElementInDeque(Vector2 element, deque<Vector2> body){//compares two coordinatess of snake body with another coordinate if they coincide or not
    for(unsigned int i=0; i < body.size(); i++){
        if(Vector2Equals(body[i],element)){
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};//this stores the coordinate information of the snake body
    Vector2 direction = {1,0};//head direction 
    void Draw(){
        
        for(unsigned int i=0; i<body.size(); i++){//iterating through each block of snake body
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x*cellSize,y*cellSize, cellSize, cellSize};//declaring the size of block
            DrawRectangleRounded(segment, 0.5, 6, DARKGREEN);//drawing it 
        }
    }

    void Update(){
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));//progresses the body along the given body
    }

    void Reset(){
        body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};//resets the snake body to original location
        direction = {1, 0};
    }
};

class Food{
public:
    Vector2 position;
    Texture2D texture;
    
    Food(deque<Vector2> snakeBody){//input is snakeBody so that apple is not generated inside of the body of snake
        Image appleImage = LoadImage("graphics/apple.png");
        texture = LoadTextureFromImage(appleImage);
        UnloadImage(appleImage);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
    }

    Vector2 generateRandomCell(){//generates a random cell position in the grid for apple
        float x = GetRandomValue(0, cellHCount - 1);
        float y = GetRandomValue(0, cellVCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody){

        Vector2 position = generateRandomCell();//apple position
        while(ElementInDeque(position, snakeBody)){
            position = generateRandomCell();//if condition is true new random position generated
        }
        return position;
    }
};

class Game{
public:
    Food apple = Food(snake.body);
    Snake snake = Snake();
    bool running = true;

    void Draw(){
        apple.Draw();
        snake.Draw();
    }

    void Update(){
        if(running){
            snake.Update();
            checkCollisionWithEdges();
            checkCollisionWithBody();
            eatFood();
        }
        
    }

    void eatFood(){
        if(apple.position == snake.body[0]){
            apple.position = apple.GenerateRandomPos(snake.body);
            snake.body.push_back(Vector2Subtract(snake.body[snake.body.size()-1],snake.direction));
        }

    }

    void checkCollisionWithEdges(){
        if(snake.body[0].x == cellHCount || snake.body[0].x == -1){
            GameOver();
        }
        if(snake.body[0].y == cellVCount || snake.body[0].y == -1){
            GameOver();
        }
    }

    void checkCollisionWithBody(){
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0], headlessBody)){
            GameOver();
        }
    }

    void GameOver(){
        snake.Reset();
        apple.position = apple.GenerateRandomPos(snake.body);
        running = false;
    }
};

int main(){

    InitWindow(2*offset + cellSize*cellHCount,2*offset + cellSize*cellVCount,"Snake");
    SetTargetFPS(60);
    ToggleFullscreen();

    Game game = Game();

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GrassGreen);

        if(eventTriggered(0.2)){
            game.Update();  
        }

        if(IsKeyDown(KEY_UP) && game.snake.direction.y != 1){
            game.snake.direction = {0, -1}; 
            game.running = true;
        }
        if(IsKeyDown(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction = {0, 1};
            game.running = true;
        }
        if(IsKeyDown(KEY_RIGHT) && game.snake.direction.x != -1){
            game.snake.direction = {1, 0};
            game.running = true;
        }
        if(IsKeyDown(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = {-1,0};
            game.running = true;
        }
        

        //Drawing
        game.Draw();
        
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
