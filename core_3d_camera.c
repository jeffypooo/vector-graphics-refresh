#include "raylib.h"

// ----------------------------------------------------------------------------------
// Program main entry point
// ----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Setup camera
    Camera3D camera = { 
        .position = { 0.0f, 10.0f, 10.0f },
        .target = { 0.0f, 0.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
     };

     // Cube to render
     Vector3 cubePos = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(120);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        // Update
        // ----------------------------------------------------------------------------------
        // ----------------------------------------------------------------------------------

        // Draw
        // ----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePos, 2.0f, 2.0f, 2.0f, SKYBLUE);
                DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, RED);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("3D Mode Example", 10, 40, 20, RED);
            DrawFPS(10, 10);
        
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}