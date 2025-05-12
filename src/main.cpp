#include <raylib.h>
#include <iostream>
using namespace std;

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};
int cellSize = 30 ;
int cellCount= 25;


class food{
    public:
    Vector2 position = {5,10};

    void Draw(){
        DrawRectangle(position.x * cellSize , position.y * cellSize , cellSize , cellSize, darkGreen);
    };
};

int main() 
{
    cout << "Hello, World!" << endl;

    InitWindow(cellSize*cellCount,cellSize*cellCount,"Retro Snake");
  
    SetTargetFPS(60); // Set the target frames-per-second
    while(WindowShouldClose()== false){ // Detect window close button or ESC key{
     BeginDrawing();

      food myFood;

         ClearBackground(green);

         myFood.Draw();

            EndDrawing();

    }

     CloseWindow();

    return 0;
};
