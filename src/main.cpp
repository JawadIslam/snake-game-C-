#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
int cellSize = 30;
int cellCount = 25;

int lastupdateTime = 0;

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

    food()
    {
        Image image = LoadImage("food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GetRandomPosition();
    }
    ~food()
    {
        UnloadTexture(texture);
    };

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    };

    Vector2 GetRandomPosition()
    {

        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);

        return Vector2{x, y};
    };
};

class snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

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
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    };
};

class game
{

public:
    food myfood = food();
    snake mysnake = snake();

    void Draw()
    {

        myfood.Draw();
        mysnake.Draw();
    };

    void update()
    {
        mysnake.update();
        checkCollision();
    };

    void checkCollision(){
        if( Vector2Equals(mysnake.body[0], myfood.position) ){
            cout << "foodeatten" << endl;
            myfood.Draw();
        };
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

        if (eventtriggered(0.2))
        {
            mygame.update();
        };

        if (IsKeyPressed(KEY_UP) && mygame.mysnake.direction.y != 1)
        {
            mygame.mysnake.direction = {0, -1};
        };

        if (IsKeyPressed(KEY_DOWN) && mygame.mysnake.direction.y != -1)
        {
            mygame.mysnake.direction = {0, 1};
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
