#pragma once

#include <raygui.h>
#include <raylib.h>

const float CELL_SIZE = 50;

Vector2 GetBoardSize();
void DrawTextureSize(Texture texture, Rectangle rec, Color color);
void DrawTextureSizeEx(Texture texture, Rectangle rec, Vector2 origin, float rotation, Color color);
void DrawRectangleRecCentered(Vector2 size, Color color);
void DrawTextCentered(const char* text, float posY, int fontSize, Color color);
bool DrawButtonCentered(Vector2 size, float posY, const char* text);
void DrawIcon(int iconId, int posX, int posY, float size, Color color);
