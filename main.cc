#include "raylib.h"
#include <math.h>
#include <stdio.h>
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

typedef struct Player
{
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
} Player;

// typedef struct Shoot
// {
//     Vector2 position;
//     Vector2 speed;
//     float radius;
//     float rotation;
//     int lifeSpawnn;
//     bool active;
//     Color color;
// } Shoot;

// ---------------
// global variable declaration
// ---------------
static const unsigned int screenWidth = 800;
static const unsigned int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;
static bool victory = false;

static float shipHeight = 0.0f;

static Player player = {0};
// static Shoot shoot[PLAYER_MAX_SHOOTS] = {0};

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
    InitGame();
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

void InitGame(void)
{
    int posX, posY;
    int velX, velY;
    victory = false;
    pause = false;

    shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);

    // init the player
    player.position = (Vector2){screenWidth / 2, screenHeight / 2 - shipHeight / 2};
    player.speed = (Vector2){0, 0};
    player.acceleration = 0;
    player.rotation = 0;
    player.collider = (Vector3){
        player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f),
        player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f),
        12};
    player.color = LIGHTGRAY;
}

void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P'))
        {
            pause = !pause;
        }
        if (!pause)
        {
            // rotation
            if (IsKeyDown(KEY_LEFT))
            {
                player.rotation -= 5;
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                player.rotation += 5;
            }
            // player speed
            player.speed.x = sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
            player.speed.y = cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
            // player acceleration
            if (IsKeyDown(KEY_UP))
            {
                if (player.acceleration < 1)
                    player.acceleration += 0.04f;
            }
            else
            {
                if (player.acceleration > 0)
                    player.acceleration -= 0.02f;
                else if (player.acceleration < 0)
                    player.acceleration = 0;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                if (player.acceleration > 0)
                    player.acceleration -= 0.04f;
                else if (player.acceleration < 0)
                    player.acceleration = 0;
            }

            // player movement
            player.position.x += (player.speed.x * player.acceleration);
            player.position.y -= (player.speed.y * player.acceleration);
        }

        if (IsKeyPressed('X'))
        {
            InitGame();
            gameOver = true;
        }
        if (IsKeyPressed('W'))
        {
            InitGame();
            victory = true;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
        return;
    }
}

void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (!gameOver)
    {
        // draw spaceship
        Vector2 v1 = {player.position.x + sinf(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cosf(player.rotation * DEG2RAD) * (shipHeight)};
        Vector2 v2 = {player.position.x - cosf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2)};
        Vector2 v3 = {player.position.x + cosf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2)};
        DrawTriangle(v1, v2, v3, MAROON);

        if (victory)
            DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);

        if (pause)
            DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    EndDrawing();
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
};

/* steps
make the screen states
draw the player
add movement
add shooting
add asteroids
add collision
add breaking of asteroids
*/