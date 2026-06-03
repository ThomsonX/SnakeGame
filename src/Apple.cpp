#include "Apple.hpp"
#include "Utils.hpp"
#include <raylib.h>

Apple apple;

void Apple::Init()
{
    texture = LoadTexture("resources/apple.png");

    Reset();
}

void Apple::Reset()
{
    Vector2 boardSize = GetBoardSize();
    position = {(float)GetRandomValue(0, boardSize.x - 1),
                (float)GetRandomValue(0, boardSize.y - 1)};
}

void Apple::Draw()
{
    DrawTextureSize(texture, {position.x * CELL_SIZE, position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE},
                    WHITE);
}
