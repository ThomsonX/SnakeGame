#include <cmath>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>
#include <vector>

const float CELL_SIZE = 50;

Vector2 GetBoardSize()
{
    return {(float)floor(GetRenderWidth() / CELL_SIZE),
            (float)floor(GetRenderHeight() / CELL_SIZE)};
}

struct Apple
{
    Vector2 position{2, 2};
    Texture2D texture = LoadTexture("resources/apple.png");

    void SetRandomPosition()
    {
        Vector2 boardSize = GetBoardSize();
        position = {(float)GetRandomValue(0, boardSize.x), (float)GetRandomValue(0, boardSize.y)};
    }
    void Draw()
    {
        DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height},
                       {position.x * CELL_SIZE, position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE},
                       {0, 0}, 0, WHITE);
    }
};

enum Direction
{
    Left,
    Right,
    Up,
    Down
};

struct Snake
{
    std::vector<Vector2> body = {{2, 0}, {1, 0}, {0, 0}};
    Direction direction = Right;

    void Move(bool removeLast = true)
    {
        Vector2 head = body[0];
        switch (direction)
        {
        case Left:
            head.x -= 1;
            break;
        case Right:
            head.x += 1;
            break;
        case Up:
            head.y -= 1;
            break;
        case Down:
            head.y += 1;
            break;
        }

        Vector2 boardSize = GetBoardSize();
        if (head.x < 0) head.x = boardSize.x - 1;
        if (head.x > boardSize.x - 1) head.x = 0;
        if (head.y < 0) head.y = boardSize.y - 1;
        if (head.y > boardSize.y - 1) head.y = 0;

        body.insert(body.begin(), head);
        if (removeLast) body.pop_back();
    }

    void HandleCollision(Apple& apple)
    {
        if (apple.position == body[0])
        {
            apple.SetRandomPosition();
            Move(false);
        }
    }

    void Update()
    {
        if (IsKeyPressed(KEY_LEFT) && direction != Right) direction = Left;
        if (IsKeyPressed(KEY_RIGHT) && direction != Left) direction = Right;
        if (IsKeyPressed(KEY_UP) && direction != Down) direction = Up;
        if (IsKeyPressed(KEY_DOWN) && direction != Up) direction = Down;
    }

    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            Color color = ColorLerp(GREEN, WHITE, i * 1.0 / body.size());
            DrawRectangle(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                          color);
        }
    }
};

int main()
{
    srand(time(0));

    InitWindow(800, 600, "raylib");
    SetTargetFPS(60);

    double timer = GetTime();
    double tickTime = 0.2;

    Snake snake;
    Apple apple;
    apple.SetRandomPosition();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (GetTime() - timer >= tickTime)
        {
            snake.Move();
            snake.HandleCollision(apple);
            timer = GetTime();
        }

        snake.Update();

        snake.Draw();
        apple.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
