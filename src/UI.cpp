#include "UI.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <raylib.h>
#include <string>

Sound hihihiha_mp3;
Sound munch;
Sound sigeon_pex;
Sound game_over;

bool deadlyWalls = false;
bool isGameOver = false;
bool isSettings = false;
bool hihihiha = false;
bool gameOverSound = false;
int appleCount = 1;
int score = 0;
int highScore = 0;

const Vector2 recSize = {500, 400};
const Color bgColor = ColorAlpha(GRAY, 0.5);
const float padding = 20, margin = 30;
const float fontSize = 24;
const Vector2 buttonSize = {160, 50};

void LoadSounds()
{
    // hihihiha ;)
    hihihiha_mp3 = LoadSound("resources/music/hihihiha.mp3");
    munch = LoadSound("resources/music/munch.mp3");
    sigeon_pex = LoadSound("resources/music/sigeon_pex.mp3");
    game_over = LoadSound("resources/music/game_over.mp3");

    SetSoundVolume(game_over, 0.35f);
    SetSoundVolume(sigeon_pex, 1.0f);
}

void RestartGame()
{
    isGameOver = false;
    score = 0;
    snake.Reset();

    apples.clear();
    for (int i = 0; i < appleCount; i++)
    {
        Apple apple;
        apple.Init();
        while (IsPositionOnApple(apple.position, apples)) apple.Reset();
        apples.push_back(apple);
    }
}

void GameOver()
{
    isGameOver = true;
    if (gameOverSound)
        PlaySound(sigeon_pex);
    else
        PlaySound(game_over);
    if (score > highScore) highScore = score;
}

void DrawGameMenu()
{
    const float buttonSize = 32;

    DrawText(("Score: " + std::to_string(score)).c_str(), 0, 0, fontSize * 1.5, WHITE);

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

    DrawTextCentered("Game Over!", posY, fontSize * 2, RED);
    posY += fontSize * 2 + padding;

    DrawTextCentered(("High score: " + std::to_string(highScore)).c_str(), posY, fontSize,
                     score == highScore ? YELLOW : WHITE);
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
    DrawRectangleRecCentered(recSize, GRAY);

    float posY = GetScreenHeight() / 2.0f - recSize.y / 2.0f + margin;

    DrawTextCentered("Settings", posY, fontSize, RED);
    posY += fontSize + padding;

    const char* modeText = deadlyWalls ? "Mode: Deadly Walls" : "Mode: Looping";
    if (DrawButtonCentered(buttonSize, posY, modeText))
    {
        deadlyWalls = !deadlyWalls;
    }
    posY += buttonSize.y + padding;
    GuiToggle(
        Rectangle{GetScreenWidth() / 2.0f - buttonSize.x / 2.0f, posY, buttonSize.x, buttonSize.y},
        hihihiha ? "Apple sound: hihihiha" : "Apple sound: munch", &hihihiha);
    posY += buttonSize.y + padding;
    GuiToggle(
        Rectangle{GetScreenWidth() / 2.0f - buttonSize.x / 2.0f, posY, buttonSize.x, buttonSize.y},
        gameOverSound ? "Game Over sound: ???" : "Game Over sound: trumpet", &gameOverSound);
    posY += buttonSize.y + padding;

    const char* appleText = TextFormat("Apples: %d", appleCount);

    int oldSize = GuiGetStyle(DEFAULT, TEXT_SIZE);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    if (GuiButton({(GetScreenWidth() / 2.0f - 50 / 2.0f - 150), posY, 50, 50}, "-"))
    {
        if (appleCount > 1) appleCount--;
    }

    DrawTextCentered(appleText, posY, fontSize, WHITE);

    if (GuiButton({(GetScreenWidth() / 2.0f - 50 / 2.0f + 150), posY, 50, 50}, "+"))
    {
        if (appleCount < 9) appleCount++;
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, oldSize);
}
