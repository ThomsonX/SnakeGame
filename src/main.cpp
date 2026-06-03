#include "Apple.hpp"
#include "Snake.hpp"
#include "UI.hpp"
#include <cstdlib>
#include <ctime>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
    srand(time(0));

    unsigned int flags = 0;
    flags |= FLAG_WINDOW_RESIZABLE;
    SetConfigFlags(flags);

    InitWindow(800, 600, "Snake");
    SetTargetFPS(60);

    const double TICK_TIME = 0.2;
    double timer = GetTime();

    snake.Init();
    apple.Init();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (!isGameOver && !isSettings)
        {
            if (GetTime() - timer >= TICK_TIME)
            {
                snake.Move();
                snake.HandleCollision(apple);
                timer = GetTime();
            }

            snake.Update();
        }

        snake.Draw();
        apple.Draw();
        DrawGameMenu();
        if (isGameOver) DrawGameOver();
        if (isSettings) DrawSettings();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
