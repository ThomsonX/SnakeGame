#include "Utils.hpp"
#include <cmath>
#include <raygui.h>
#include <raylib.h>

#ifndef RAYGUI_ICON_SIZE
#define RAYGUI_ICON_SIZE 16
#endif

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
