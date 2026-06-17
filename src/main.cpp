#include "Apple.hpp"
#include "Snake.hpp"
#include "UI.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
    srand(time(0));

    unsigned int flags = 0;
    flags |= FLAG_VSYNC_HINT;
    flags |= FLAG_WINDOW_RESIZABLE;
    SetConfigFlags(flags);

    InitWindow(800, 600, "Snake");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(8192);
    LoadSounds();

    const std::string highScorePath = "high_score.txt";
    {
        std::ifstream file(highScorePath);
        file >> highScore;
    }

    const double TICK_TIME = 0.2;
    double timer = GetTime();

    snake.Init();
    RestartGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (!isGameOver && !isSettings)
        {
            if (GetTime() - timer >= TICK_TIME)
            {
                snake.Move();
                snake.HandleCollision(apples);
                timer = GetTime();
            }

            snake.Update();
        }

        snake.Draw();
        for (int i = 0; i < apples.size(); i++) apples[i].Draw();
        DrawGameMenu();
        if (isGameOver) DrawGameOver();
        if (isSettings) DrawSettings();

        EndDrawing();
    }

    {
        std::ofstream file(highScorePath);
        file << highScore;
    }

    CloseWindow();
    return 0;
}
