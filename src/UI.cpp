#include "UI.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <raylib.h>

bool deadlyWalls = false;
bool isGameOver = false;
bool isSettings = false;

const Vector2 recSize = {500, 400};
const Color bgColor = ColorAlpha(GRAY, 0.5);
const float padding = 20, margin = 30;
const float fontSize = 24;
const Vector2 buttonSize = {160, 50};

void RestartGame()
{
    isGameOver = false;
    snake.Reset();
    apple.Reset();
}

void DrawGameMenu()
{
    const float buttonSize = 32;

    if (GuiButton({(float)GetRenderWidth() - buttonSize, 0, buttonSize, buttonSize}, ""))
    {
        isSettings = !isSettings;
    }
    DrawIcon(ICON_GEAR, (float)GetRenderWidth() - buttonSize, 0, buttonSize, GRAY);

    if (GuiButton({(float)GetRenderWidth() - buttonSize * 2, 0, buttonSize, buttonSize}, ""))
    {
        RestartGame();
    }
    DrawIcon(ICON_REPEAT, (float)GetRenderWidth() - buttonSize * 2, 0, buttonSize, GRAY);
}

void DrawGameOver()
{
    DrawRectangleRecCentered(recSize, bgColor);

    float posY = GetScreenHeight() / 2.0f - recSize.y / 2.0f + margin;

    DrawTextCentered("Game Over!", posY, fontSize, RED);
    posY += fontSize + padding;

    posY = std::max(posY, GetScreenHeight() / 2.0f - buttonSize.y / 2.0f);

    if (DrawButtonCentered(buttonSize, posY, "Restart"))
    {
        RestartGame();
    }
    posY += buttonSize.y + padding;
}

void DrawSettings()
{
    DrawRectangleRecCentered(recSize, bgColor);

    float posY = GetScreenHeight() / 2.0f - recSize.y / 2.0f + margin;

    DrawTextCentered("Settings", posY, fontSize, RED);
    posY += fontSize + padding;

    const char* modeText = deadlyWalls ? "Mode: Deadly Walls" : "Mode: Looping";
    if (DrawButtonCentered(buttonSize, posY, modeText))
    {
        deadlyWalls = !deadlyWalls;
    }
    posY += buttonSize.y + padding;
}
