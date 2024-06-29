#include "raylib.h"
#include <math.h>
// https://github.com/raysan5/raylib-games/blob/master/classics/src/asteroids.c

// ---------------
// defines
// ---------------
#define PLAYER_BASE_SIZE 20.0f
#define PLAYER_SPEED 6.0f
#define PLAYER_MAX_SHOOTS 10

#define METEORS_SPEED 2
#define MAX_BIG_METEORS 4
#define MAX_MEDIUM_METEORS 8
#define MAX_SMALL_METEORS 16

// ---------------
// types and struct definition
// ---------------
typedef enum GameScreen
{
    SCREEN_TITLE = 0,
    SCREEN_GAME,
} GameScreen;

// ---------------
// global variable declaration
// ---------------
static const unsigned int screenWidth = 800;
static const unsigned int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;
static bool victory = false;

static float shipHeight = 0.0f;

// ---------------
// module functions declaration (local)
// ---------------
static void InitGame(void);
static void UpdateGame(void); // update 1 frame
static void DrawGame(void);   // draw 1 frame
static void UnloadGame(void);
static void UpdateDrawFrame(void); // update and draw 1 frame

// ---------------
// program entry point
// ---------------
int main(void)
{
    InitWindow(screenWidth, screenHeight, "Asteroids");
    // InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadGame();
    CloseWindow();
    return 0;
}

// ---------------
// module functions declaration (local)
// ---------------
void UnloadGame(void) {}
void InitGame(void) {}
void UpdateGame(void)
{
    if (gameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
    else
    {
    }
}
void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (gameOver)
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    else
    {

        DrawText("TEMP TEXT", GetScreenWidth() / 2 - MeasureText("temp tetx ", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    EndDrawing();
}
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
};
