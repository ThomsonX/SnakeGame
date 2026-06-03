#include "Snake.hpp"
#include "Apple.hpp"
#include "UI.hpp"
#include "Utils.hpp"
#include <raylib.h>
#include <raymath.h>

Snake snake;

void Snake::Init()
{
    headTexture = LoadTexture("resources/snake_head.png");
    headDeadTexture = LoadTexture("resources/snake_head_dead.png");
    bodyTexture = LoadTexture("resources/snake_body.png");
    cornerTexture = LoadTexture("resources/snake_corner.png");
    tailTexture = LoadTexture("resources/snake_tail.png");

    Reset();
}

void Snake::Reset()
{
    body = {
        {{2, 0}, Direction::Right},
        {{1, 0}, Direction::Right},
        {{0, 0}, Direction::Right},
    };
    direction = Direction::Right;
    nextDirection = Direction::Right;
    lastBodyPiece = body.back();
}

void Snake::Move()
{
    direction = nextDirection;

    Vector2 head = body[0].pos;
    switch (direction)
    {
    case Direction::Left:
        head.x -= 1;
        break;
    case Direction::Right:
        head.x += 1;
        break;
    case Direction::Up:
        head.y -= 1;
        break;
    case Direction::Down:
        head.y += 1;
        break;
    }

    Vector2 boardSize = GetBoardSize();

    if (deadlyWalls)
    {
        if (head.x < 0 || head.x > boardSize.x - 1 || head.y < 0 || head.y > boardSize.y - 1)
        {
            isGameOver = true;
            return;
        }
    }
    else
    {
        if (head.x < 0) head.x = boardSize.x - 1;
        if (head.x > boardSize.x - 1) head.x = 0;
        if (head.y < 0) head.y = boardSize.y - 1;
        if (head.y > boardSize.y - 1) head.y = 0;
    }

    body.insert(body.begin(), {head, direction});
    lastBodyPiece = body.back();
    body.pop_back();
}

void Snake::Grow() { body.push_back(lastBodyPiece); }

bool Snake::IsAppleOnSnake(const Apple& apple)
{
    for (int i = 0; i < body.size(); i++)
    {
        if (apple.position == body[i].pos) return true;
    }
    return false;
}

bool Snake::IsHeadOnBody()
{
    for (int i = 1; i < body.size(); i++)
    {
        if (body[0].pos == body[i].pos) return true;
    }
    return false;
}

void Snake::HandleCollision(Apple& apple)
{
    if (IsAppleOnSnake(apple))
    {
        Grow();
        while (IsAppleOnSnake(apple)) apple.Reset();
    }
    if (IsHeadOnBody())
    {
        isGameOver = true;
        RollBack();
    }
}

void Snake::RollBack()
{
    body.push_back(lastBodyPiece);
    body.erase(body.begin());
    direction = body[0].direction;
}

void Snake::Update()
{
    if (IsKeyPressed(KEY_LEFT) && direction != Direction::Right) nextDirection = Direction::Left;
    if (IsKeyPressed(KEY_RIGHT) && direction != Direction::Left) nextDirection = Direction::Right;
    if (IsKeyPressed(KEY_UP) && direction != Direction::Down) nextDirection = Direction::Up;
    if (IsKeyPressed(KEY_DOWN) && direction != Direction::Up) nextDirection = Direction::Down;
}

void Snake::Draw()
{
    for (int i = 0; i < body.size(); i++)
    {
        float rotation = 0;
        Direction direction = body[i].direction;
        if (i > 0) direction = body[i - 1].direction;
        switch (direction)
        {
        case Direction::Up:
            rotation = 0;
            break;
        case Direction::Right:
            rotation = 90;
            break;
        case Direction::Down:
            rotation = 180;
            break;
        case Direction::Left:
            rotation = 270;
            break;
        }

        Texture texture = bodyTexture;
        if (i == 0)
        {
            if (isGameOver)
                texture = headDeadTexture;
            else
                texture = headTexture;
        }
        else if (i == body.size() - 1)
        {
            texture = tailTexture;
        }
        else if (i > 0 && body[i].direction != body[i - 1].direction)
        {
            texture = cornerTexture;
            if (body[i].direction == Direction::Up)
            {
                if (body[i - 1].direction == Direction::Right) rotation = 0;
                if (body[i - 1].direction == Direction::Left) rotation = 90;
            }
            else if (body[i].direction == Direction::Right)
            {
                if (body[i - 1].direction == Direction::Down) rotation = 90;
                if (body[i - 1].direction == Direction::Up) rotation = 180;
            }
            else if (body[i].direction == Direction::Down)
            {
                if (body[i - 1].direction == Direction::Left) rotation = 180;
                if (body[i - 1].direction == Direction::Right) rotation = 270;
            }
            else if (body[i].direction == Direction::Left)
            {
                if (body[i - 1].direction == Direction::Up) rotation = 270;
                if (body[i - 1].direction == Direction::Down) rotation = 0;
            }
        }

        DrawTextureSizeEx(texture,
                          {
                              body[i].pos.x * CELL_SIZE + CELL_SIZE / 2,
                              body[i].pos.y * CELL_SIZE + CELL_SIZE / 2,
                              CELL_SIZE,
                              CELL_SIZE,
                          },
                          {CELL_SIZE / 2, CELL_SIZE / 2}, rotation, WHITE);
    }
}
