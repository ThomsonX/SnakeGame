#include "Apple.hpp"
#include "Utils.hpp"
#include <raylib.h>
#include <raymath.h>
#include <vector>

std::vector<Apple> apples;

bool IsAppleOnApple(const std::vector<Apple>& apples)
{
    for (int i = 0; i < apples.size(); i++)
    {
        for (int j = i + 1; j < apples.size(); j++)
        {
            if (apples[i].position == apples[j].position) return true;
        }
    }
    return false;
}

bool IsPositionOnApple(Vector2 position, const std::vector<Apple>& apples)
{
    for (int i = 0; i < apples.size(); i++)
    {
        if (apples[i].position == position)
        {
            return true;
        }
    }
    return false;
}

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
