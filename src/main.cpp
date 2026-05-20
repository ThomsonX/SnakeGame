#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <ctime>

int size = 50;

Vector2 GetBoardSize()
{
    return {(float)floor(GetRenderWidth() / size), (float)floor(GetRenderHeight() / size)};
}

struct Apple
{
    Vector2 position{2, 2};

    void RandomPlacement()
    {
        Vector2 boardSize = GetBoardSize();
        position = {(float)(rand() % (int)boardSize.x), (float)(rand() % (int)boardSize.y)};
    }

    void Draw()
    {
        // DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, WHITE);
        DrawRectangle(position.x * size, position.y * size, size, size, RED);
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

    void Move(bool removeLast)
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
        if (head.x < 0)
            head.x = boardSize.x - 1;
        if (head.x > boardSize.x - 1)
            head.x = 0;
        if (head.y < 0)
            head.y = boardSize.y - 1;
        if (head.y > boardSize.y - 1)
            head.y = 0;

        body.insert(body.begin(), head);
        if (removeLast)
            body.pop_back();
    }

    void HandleCollision(Apple& apple)
    {
        if (apple.position == body[0])
        {
            apple.RandomPlacement();
            Move(false);
        }
    }

    void Update()
    {
        Move(true);
    }

    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            // DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, WHITE);
            DrawRectangle(body[i].x * size, body[i].y * size, size, size, ColorLerp(GREEN, WHITE, i * 1.0 / body.size()));
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
    apple.RandomPlacement();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (GetTime() - timer >= tickTime)
        {
            snake.Update();
            snake.HandleCollision(apple);
            timer = GetTime();
        }

        if (IsKeyPressed(KEY_LEFT) && snake.direction != Right)
            snake.direction = Left;
        if (IsKeyPressed(KEY_RIGHT) && snake.direction != Left)
            snake.direction = Right;
        if (IsKeyPressed(KEY_UP) && snake.direction != Down)
            snake.direction = Up;
        if (IsKeyPressed(KEY_DOWN) && snake.direction != Up)
            snake.direction = Down;

        snake.Draw();
        apple.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
