#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
using namespace std;
//  second commit

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
bool running;
int lastupdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{

    for (unsigned int i = 0; i < deque.size(); i++)
    {

        if (Vector2Equals(deque[i], element))
        {
            return true;
        };
    }

    return false;
}

bool eventtriggered(bool enterval)
{
    double currentTime = GetTime();

    if (currentTime - lastupdateTime > enterval)
    {
        lastupdateTime = currentTime;
        return true;
    };

    return false;
};

class food
{
public:
    Vector2 position;
    Texture2D texture;

    food(deque<Vector2> snakebody)
    {
        Image image = LoadImage("food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GetRandomPosition(snakebody);
    }
    ~food()
    {
        UnloadTexture(texture);
    };

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    };

    Vector2 GenerateRandomcell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);

        return Vector2{x, y};
    }

    Vector2 GetRandomPosition(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomcell();

        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomcell();
        };

        return position;
    };
};

class snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;
    void Draw()
    {

        for (unsigned int i = 0; i < body.size(); i++)
        {

            float x = body[i].x;
            float y = body[i].y;

            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        };
    };

    void update()
    {

        body.push_front(Vector2Add(body[0], direction));

        if (addSegment == true)
        {

            addSegment = false;
        }

        else
        {
            body.pop_back();
        }
    };

// update

     void Reset(){
        body={Vector2{6,9} ,Vector2{5,9} , Vector2{4,9}};
        direction = {1,0};
    
    }
};
    

class game
{

public:
    snake mysnake = snake();
    food myfood = food(mysnake.body);
    bool running = false;
    void Draw()
    {
        myfood.Draw();
        mysnake.Draw();
    };

    void update(){
    if(running){
        checkCollision();
        CheckCollisionWithedge();
    };
};
    void checkCollision()
    {
        if (Vector2Equals(mysnake.body[0], myfood.position))
        {
            cout << "foodeatten" << endl;
            myfood.position = myfood.GetRandomPosition(mysnake.body);
            mysnake.addSegment = true;
        };
    };

    void CheckCollisionWithedge(){
        if(mysnake.body[0].x == cellSize || mysnake.body[0].x == -1){
           GameOver();           

        };
        if(mysnake.body[0].y == cellSize || mysnake.body[0].y == -1){
            GameOver();
        };
    };

     void GameOver(){
      mysnake.Reset(); 
      myfood.position = myfood.GetRandomPosition(mysnake.body);
      running = false;
     };

};

int main()
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");

    SetTargetFPS(60); 
    game mygame = game();
    while (WindowShouldClose() == false)
    {
        // Detect window close button or ESC key

        BeginDrawing();

        if (eventtriggered(0.5))
        {
            mygame.update();
        };
// update
        if (IsKeyPressed(KEY_UP) && mygame.mysnake.direction.y != 1)
        {
            mygame.mysnake.direction = {0, -1};
            mygame.runnig = true;
        };

        if (IsKeyPressed(KEY_DOWN) && mygame.mysnake.direction.y != -1)
        {
            mygame.mysnake.direction = {0, 1};
            game.running = true
        };
        if (IsKeyPressed(KEY_LEFT) && mygame.mysnake.direction.x != 1)
        {
            mygame.mysnake.direction = {-1, 0};
        };

        if (IsKeyPressed(KEY_RIGHT) && mygame.mysnake.direction.x != -1)
        {
            mygame.mysnake.direction = {1, 0};
         
        };
        ClearBackground(green);

        mygame.Draw();


        EndDrawing();
    };

    CloseWindow();
    return 0;
};
