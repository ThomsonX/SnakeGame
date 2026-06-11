#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

const float CELL_SIZE = 50;

bool deadlyWalls = false;
bool isGameOver = false;
bool isSettings = false;
bool hihihiha = false;
Sound hihihiha_mp3;
Sound munch;

Vector2 GetBoardSize()
{
    return {(float)floor(GetRenderWidth() / CELL_SIZE),
            (float)floor(GetRenderHeight() / CELL_SIZE)};
}

void DrawTextureSize(Texture texture, Rectangle rec, Color color)
{
    DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, rec, {0, 0}, 0,
                   color);
}

void DrawTextureSizeEx(Texture texture, Rectangle rec, Vector2 origin, float rotation, Color color)
{
    DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, rec, origin,
                   rotation, color);
}

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

bool DrawButtonCentered(Vector2 size, float posY, const char* text)
{
    return GuiButton({(GetScreenWidth() / 2.0f - size.x / 2.0f), posY, size.x, size.y}, text);
}

void DrawIcon(int iconId, int posX, int posY, float size, Color color)
{
    GuiDrawIcon(iconId, posX, posY, size / RAYGUI_ICON_SIZE, color);
}

struct Apple
{
    Vector2 position{2, 2};
    Texture texture;

    void Init()
    {
        texture = LoadTexture("resources/apple.png");

        Reset();
    }

    void Reset()
    {
        Vector2 boardSize = GetBoardSize();
        position = {(float)GetRandomValue(0, boardSize.x - 1),
                    (float)GetRandomValue(0, boardSize.y - 1)};
    }

    void Draw()
    {
        DrawTextureSize(
            texture, {position.x * CELL_SIZE, position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, WHITE);
    }
};

Apple apple;

enum Direction
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

    void Init()
    {
        headTexture = LoadTexture("resources/snake_head.png");
        headDeadTexture = LoadTexture("resources/snake_head_dead.png");
        bodyTexture = LoadTexture("resources/snake_body.png");
        cornerTexture = LoadTexture("resources/snake_corner.png");
        tailTexture = LoadTexture("resources/snake_tail.png");

        Reset();
    }

    void Reset()
    {
        body = {
            {{2, 0}, Right},
            {{1, 0}, Right},
            {{0, 0}, Right},
        };
        direction = Right;
        nextDirection = Right;
        lastBodyPiece = body.back();
    }

    void Move()
    {
        direction = nextDirection;

        Vector2 head = body[0].pos;
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

    void Grow() { body.push_back(lastBodyPiece); }

    bool IsAppleOnSnake(const Apple& apple)
    {
        for (int i = 0; i < body.size(); i++)
        {
            if (apple.position == body[i].pos) return true;
        }
        return false;
    }

    bool IsHeadOnBody()
    {
        for (int i = 1; i < body.size(); i++)
        {
            if (body[0].pos == body[i].pos) return true;
        }
        return false;
    }

    void HandleCollision(Apple& apple)
    {
        if (IsAppleOnSnake(apple))
        {
            Grow();
            if (hihihiha == true) PlaySound(hihihiha_mp3);
            else PlaySound(munch);
            while (IsAppleOnSnake(apple)) apple.Reset();
        }
        if (IsHeadOnBody())
        {
            isGameOver = true;
            RollBack();
        }
    }

    void RollBack()
    {
        body.push_back(lastBodyPiece);
        body.erase(body.begin());
        direction = body[0].direction;
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
            float rotation = 0;
            Direction direction = body[i].direction;
            if (i > 0) direction = body[i - 1].direction;
            switch (direction)
            {
            case Up:
                rotation = 0;
                break;
            case Right:
                rotation = 90;
                break;
            case Down:
                rotation = 180;
                break;
            case Left:
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
                if (body[i].direction == Up)
                {
                    if (body[i - 1].direction == Right) rotation = 0;
                    if (body[i - 1].direction == Left) rotation = 90;
                }
                else if (body[i].direction == Right)
                {
                    if (body[i - 1].direction == Down) rotation = 90;
                    if (body[i - 1].direction == Up) rotation = 180;
                }
                else if (body[i].direction == Down)
                {
                    if (body[i - 1].direction == Left) rotation = 180;
                    if (body[i - 1].direction == Right) rotation = 270;
                }
                else if (body[i].direction == Left)
                {
                    if (body[i - 1].direction == Up) rotation = 270;
                    if (body[i - 1].direction == Down) rotation = 0;
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
};

Snake snake;

void RestartGame()
{
    isGameOver = false;
    snake.Reset();
    apple.Reset();
}

const Vector2 recSize = {500, 400};
const float padding = 20, margin = 30;
const float fontSize = 24;
const Vector2 buttonSize = {160, 50};

void DrawGameOver()
{
    DrawRectangleRecCentered(recSize, GRAY);

    float posY = GetScreenHeight() / 2.0f - recSize.y / 2.0f + margin;

    DrawTextCentered("Game Over!", posY, fontSize, RED);
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
GuiToggle((Rectangle)
    {
    GetScreenWidth() / 2.0f - buttonSize.x / 2.0f,posY,buttonSize.x,buttonSize.y
    },
    hihihiha ? "ON ???" : "OFF ???",
    &hihihiha
);
}

int main()
{
    srand(time(0));

    unsigned int flags = 0;
    flags |= FLAG_VSYNC_HINT;
    flags |= FLAG_WINDOW_RESIZABLE;
    SetConfigFlags(flags);

    InitWindow(800, 600, "Snake");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
  
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(8192);
    hihihiha_mp3 = LoadSound("resources/hihihiha.mp3");
    munch = LoadSound("resources/munch.mp3");

    const double TICK_TIME = 0.2;
    double timer = GetTime();

    snake.Init();
    apple.Init();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        if (!isGameOver && !isSettings)
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
        const float buttonSize = 32;
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
        if (isGameOver) DrawGameOver();
        if (isSettings) DrawSettings();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
