#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

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
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
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

            Rectangle segment = Rectangle{offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};

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

    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class game
{

public:
    snake mysnake = snake();
    food myfood = food(mysnake.body);
    bool running = true;
    int score = 0;

    void Draw()
    {
        myfood.Draw();
        mysnake.Draw();
    };

    void update()
    {
        if (running)
        {
            mysnake.update();
            checkCollision();
            CheckCollisionWithedge();
        };
    };
    void checkCollision()
    {
        if (Vector2Equals(mysnake.body[0], myfood.position))
        {
            cout << "foodeatten" << endl;
            score++;
            myfood.position = myfood.GetRandomPosition(mysnake.body);
            mysnake.addSegment = true;
        };
    };

    void CheckCollisionWithedge()
    {
        if (mysnake.body[0].x == cellCount || mysnake.body[0].x < 0)
        {
            GameOver();
        };
        if (mysnake.body[0].y == cellCount || mysnake.body[0].y < 0)
        {
            GameOver();
        };
    };

    void GameOver()
    {
        mysnake.Reset();
        myfood.position = myfood.GetRandomPosition(mysnake.body);
        running = false;
    };
};

int main()
{
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Retro Snake");

    SetTargetFPS(50);
    game mygame = game();
    while (WindowShouldClose() == false)
    {
        // Detect window close button or ESC key

        BeginDrawing();

        if (eventtriggered(0.8))
        {
            mygame.update();
        };
        // update
        if (IsKeyPressed(KEY_UP) && mygame.mysnake.direction.y != 1)
        {
            mygame.mysnake.direction = {0, -1};
            mygame.running = true;
        };

        if (IsKeyPressed(KEY_DOWN) && mygame.mysnake.direction.y != -1)
        {
            mygame.mysnake.direction = {0, 1};
            mygame.running = true;
        };
        if (IsKeyPressed(KEY_LEFT) && mygame.mysnake.direction.x != 1)
        {
            mygame.mysnake.direction = {-1, 0};
            mygame.running = true;
        };

        if (IsKeyPressed(KEY_RIGHT) && mygame.mysnake.direction.x != -1)
        {
            mygame.mysnake.direction = {1, 0};
            mygame.running = true;
        };
        ClearBackground(green);
        //  DrawRectangleLinesEx(Rectangle{(float)offset - 5 ,(float)offset - 5 ,(float)cellSize* cellCount + 10 , (float)cellSize * cellCount + 10 }, 2, darkGreen);

        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);
        DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
        mygame.Draw();
        DrawText(TextFormat("%i", mygame.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        EndDrawing();
    };

    CloseWindow();
    return 0;
};
