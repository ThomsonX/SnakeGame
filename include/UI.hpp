#pragma once

#include <raylib.h>

void LoadSounds();
void RestartGame();
void GameOver();
void DrawGameMenu();
void DrawGameOver();
void DrawSettings();

extern Sound hihihiha_mp3;
extern Sound munch;
extern Sound sigeon_pex;
extern Sound game_over;

extern bool deadlyWalls;
extern bool isGameOver;
extern bool isSettings;
extern bool hihihiha;
extern bool gameOverSound;
extern int appleCount;
extern int score;
extern int highScore;
