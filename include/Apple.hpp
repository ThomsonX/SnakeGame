#pragma once

#include <raylib.h>

struct Apple
{
    Vector2 position{2, 2};
    Texture texture;

    void Init();
    void Reset();
    void Draw();
};

extern Apple apple;
