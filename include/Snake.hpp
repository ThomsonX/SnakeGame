#pragma once

#include "Apple.hpp"
#include <raylib.h>
#include <vector>

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

struct Snake
{
    struct BodyPiece
    {
        Vector2 pos;
        Direction direction;
    };

    std::vector<BodyPiece> body;
    Direction direction, nextDirection;
    BodyPiece lastBodyPiece;
    Texture headTexture;
    Texture headDeadTexture;
    Texture bodyTexture;
    Texture cornerTexture;
    Texture tailTexture;

    void Init();
    void Reset();
    void Move();
    void Grow();
    bool IsAppleOnSnake(const Apple& apple);
    bool IsHeadOnBody();
    void HandleCollision(std::vector<Apple>& apples);
    void RollBack();
    void Update();
    void Draw();
};

extern Snake snake;
