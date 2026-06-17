#pragma once

#include <raylib.h>
#include <vector>

struct Apple
{
    Vector2 position{2, 2};
    Texture texture;

    void Init();
    void Reset();
    void Draw();
};

bool IsAppleOnApple(const std::vector<Apple>& apples);
bool IsPositionOnApple(Vector2 position, const std::vector<Apple>& apples);

extern std::vector<Apple> apples;
