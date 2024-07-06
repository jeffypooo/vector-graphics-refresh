#include "raylib.h"
#include "raymath.h"

#define GRAVITY 500.0f
#define JUMP_ACCEL 50000.0f
#define PLAYER_SPEED 200.0f

typedef struct Player {
    Vector2 pos;
    Vector2 vel;
    Vector2 accel;
    float spd;
    bool canJump;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

void UpdatePlayer(Player *player, float deltaT);


int main(void)
{
    // Initialization
    // --------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    // SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera platformer");

    // Player
    Player player = { 
        .pos = { 400, 450 },
        .vel = { 0, 0 },
        .accel = { 0, 0 },
        .spd = 0,
     };
    // Camera
    Camera2D camera = { 
        .target = player.pos,
        .offset = { screenWidth / 2.0f, screenHeight / 2.0f },
        .rotation = 0.0f,
        .zoom = 1.0f
     };

    SetTargetFPS(120);

     // --------------------------------------------------------------------------------


     // Main game loop
     while (!WindowShouldClose()) 
     {
        // Update State
        // --------------------------------------------------------------------------------
        float deltaT = GetFrameTime();
        UpdatePlayer(&player, deltaT);
        // --------------------------------------------------------------------------------

        // Draw
        // --------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            BeginMode2D(camera);

                Rectangle playerRect = { player.pos.x, player.pos.y, 40.0f, 40.0f };
                DrawRectangleRec(playerRect, GREEN);

            EndMode2D();
        
        EndDrawing();
     }

    // De-initialization
    // --------------------------------------------------------------------------------
    CloseWindow();
    // --------------------------------------------------------------------------------

    return 0;
}

void UpdatePlayer(Player *player, float deltaT)
{   
    // Handle right/left movement
    if (IsKeyDown(KEY_LEFT)) player->pos.x -= (PLAYER_SPEED * deltaT);
    if (IsKeyDown(KEY_RIGHT)) player->pos.x += (PLAYER_SPEED * deltaT);

    float floorY = 760.0f;
    bool isGrounded = player->pos.y >= floorY;
    // Acceleration
    // --------------------------------------------------------------------------------
    // Gravity 
    player->accel.y = GRAVITY;
    // check if the player is trying to jump
    if (isGrounded && IsKeyDown(KEY_SPACE))
    {
        // apply jump
        player->accel.y += -(JUMP_ACCEL);
    }
    // --------------------------------------------------------------------------------

    // Velocities
    // --------------------------------------------------------------------------------
    if (isGrounded && player->accel.y > 0) 
    {
        player->vel.y = 0;
    }
    else 
    {
        player->vel.y += player->accel.y * deltaT;
    }
    // --------------------------------------------------------------------------------

    // Position
    player->pos.y += player->vel.y * deltaT;
    if (player->pos.y >= floorY)
    {
        player->pos.y = floorY;
    }

    float textY = 40;
    DrawText(TextFormat("player accel: %.2f, %.2f", player->accel.x, player->accel.y), 40, textY, 24, RED);
    textY += 40.0f;
    DrawText(TextFormat("player vel: %.2f, %.2f", player->vel.x, player->vel.y), 40, textY, 24, RED);
    textY += 40.0f;
    DrawText(TextFormat("player pos: %.2f, %.2f, on_ground: %d", player->pos.x, player->pos.y, isGrounded), 40, textY, 24, RED);
    textY += 40.0f;
    DrawFPS(0, 0);
}