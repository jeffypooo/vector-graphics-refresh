#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

#define MOUSEWHEEL_POSITION_SCALE_F 0.05f

// ----------------------------------------------------------------------------------
// Program main entry point
// ----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera mouse zoom");

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    // Main game loop
    while (!WindowShouldClose()) 
    {
        // Update
        // ----------------------------------------------------------------------------------

        // Translate based on mouse click and drag
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom); // -1.0f to invert dragging direction
            camera.target = Vector2Add(camera.target, delta);
        }

        // Mouse Wheel Zoom
        float wheel = GetMouseWheelMove();
        if (wheel != 0) 
        {
            // Convert to wold coordinate
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            // Offset camera to mouse position
            camera.offset = GetMousePosition();
            // Set camera target to mouse coordinates in game window
            camera.target = mouseWorldPos;

            // Zoom camera based on mouse wheel movement
            float scaleFactor = 1.0f + (MOUSEWHEEL_POSITION_SCALE_F * fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
            camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
        }


        // ----------------------------------------------------------------------------------


        // Draw
        // ----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);

                rlPushMatrix();
                    rlTranslatef(0, 25 * 50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 50);
                rlPopMatrix();

                // Reference circle
                DrawCircle(
                    GetScreenWidth() / 2.0f,
                    GetScreenHeight() / 2.0f,
                    50,
                    SKYBLUE
                );
            
            EndMode2D();
        
        EndDrawing();
        // ----------------------------------------------------------------------------------
    }

    // De-initialization
    // --------------------------------------------------------------------------------------
    CloseWindow();
    // --------------------------------------------------------------------------------------

    return 0;
}