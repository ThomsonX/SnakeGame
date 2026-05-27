#include <cmath>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

const float CELL_SIZE = 50;

bool isGameOver = false;

Vector2 GetBoardSize()
{
    return {(float)floor(GetRenderWidth() / CELL_SIZE),
            (float)floor(GetRenderHeight() / CELL_SIZE)};
}

void DrawTextureSize(Texture texture, Rectangle rec)
{
    DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height},
                       rec,
                       {0, 0}, 0, WHITE);
}

struct Apple
{
    Vector2 position{2, 2};
    Texture2D texture = LoadTexture("resources/apple.png");

    void Reset()
    {
        Vector2 boardSize = GetBoardSize();
        position = {(float)GetRandomValue(0, boardSize.x - 1),
                    (float)GetRandomValue(0, boardSize.y - 1)};
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
    std::vector<Vector2> body;
    Direction direction, nextDirection;
    Vector2 lastTailPos;

    Snake() { Reset(); }

    void Reset()
    {
        body = {{2, 0}, {1, 0}, {0, 0}};
        direction = Right;
        nextDirection = Right;
        lastTailPos = body.back();
    }

    void Move()
    {
        direction = nextDirection;

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
        lastTailPos = body.back();
        body.pop_back();
    }

    void Grow() { body.push_back(lastTailPos); }

    bool IsAppleOnSnake(const Apple& apple)
    {
        for (int i = 0; i < body.size(); i++)
        {
            if (apple.position == body[i]) return true;
        }
        return false;
    }

    bool IsHeadOnBody()
    {
        for (int i = 1; i < body.size(); i++)
        {
            if (body[0] == body[i]) return true;
        }
        return false;
    }

    void HandleCollision(Apple& apple)
    {
        if (IsAppleOnSnake(apple))
        {
            Grow();
            while (IsAppleOnSnake(apple)) apple.Reset();
        }
        if (IsHeadOnBody())
        {
            isGameOver = true;
        }
    }

    void Update()
    {
        if (IsKeyPressed(KEY_LEFT) && direction != Right) nextDirection = Left;
        if (IsKeyPressed(KEY_RIGHT) && direction != Left) nextDirection = Right;
        if (IsKeyPressed(KEY_UP) && direction != Down) nextDirection = Up;
        if (IsKeyPressed(KEY_DOWN) && direction != Up) nextDirection = Down;
    }

    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            Color color = ColorLerp(GREEN, WHITE, (float)i / body.size());
            DrawRectangle(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                          color);
        }
    }
};

Snake snake;

void DrawRectangleRecCentered(Vector2 size, Color color)
{
    float posX = GetScreenWidth() / 2.0 - size.x / 2.0;
    float posY = GetScreenHeight() / 2.0 - size.y / 2.0;
    DrawRectangle(posX, posY, size.x, size.y, color);
}

void DrawTextCentered(const char* text, float posY, int fontSize, Color color)
{
    float posX = GetScreenWidth() / 2.0 - MeasureText(text, fontSize) / 2.0;
    DrawText(text, posX, posY, fontSize, color);
}

void DrawGameOver()
{
    DrawRectangleRecCentered({500, 400}, GRAY);
    DrawTextCentered("Game Over!", 50, 24, RED);

    if (GuiButton({0, 0, 100, 50}, "Restart"))
    {
        isGameOver = false;
        snake.Reset();
    }
}

int main()
{
    srand(time(0));

    int flags = 0;
    flags |= FLAG_WINDOW_RESIZABLE;
    SetConfigFlags(flags);

    InitWindow(800, 600, "Snake");
    SetTargetFPS(60);

    const double TICK_TIME = 0.2;
    double timer = GetTime();

    Apple apple;
    apple.Reset();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (!isGameOver)
        {
            if (GetTime() - timer >= TICK_TIME)
            {
                snake.Move();
                snake.HandleCollision(apple);
                timer = GetTime();
            }

            snake.Update();
        }

        snake.Draw();
        apple.Draw();
        if (isGameOver) DrawGameOver();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
