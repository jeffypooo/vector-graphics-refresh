#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define TARGET_FPS 60

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;


int main(void) 
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic screen manager");

    GameScreen currentScreen = LOGO;

    int frameCounter = 0;  // Useful to count frames

    SetTargetFPS(TARGET_FPS);      // Set our game to run at 60 frames-per-second

    // Main game loop
    while(!WindowShouldClose()) 
    {
        switch (currentScreen) {
            case LOGO:
            {

                // Update LOGO screen data here!
                
                frameCounter++;

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (frameCounter > 120) {
                    TraceLog(LOG_INFO, "LOGO screen reached the defined time... JUMP to TITLE screen");
                    currentScreen = TITLE;
                }

            } break;
            case TITLE:
            {
                // Update TITLE screen data here!
                
                if (IsKeyPressed(KEY_ENTER)) {
                    TraceLog(LOG_INFO, "JUMPING to GAMEPLAY screen");
                    currentScreen = GAMEPLAY;
                }

            } break;
            case GAMEPLAY:
            {
                // Update GAMEPLAY screen data here!
                
                if (IsKeyPressed(KEY_ENTER)) {
                    TraceLog(LOG_INFO, "JUMPING to ENDING screen");
                    currentScreen = ENDING;
                } 

            } break;
            case ENDING:
            {
                // Update ENDING screen data here!
                
                if (IsKeyPressed(KEY_ENTER)) {
                    TraceLog(LOG_INFO, "JUMPING to LOGO screen");
                    currentScreen = LOGO;
                    frameCounter = 0;
                }

            } break;
            default: break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (currentScreen) {
                case LOGO:
                {
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
                } break;
                case TITLE:
                {
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 120, 220, 20, BLUE);
                } break;
                case GAMEPLAY:
                {
                    DrawText("GAMEPLAY SCREEN", 20, 20, 40, DARKPURPLE);
                    DrawText("PRESS ENTER to JUMP to ENDING SCREEN", 130, 220, 20, PURPLE);
                } break;
                case ENDING:
                {
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER to JUMP back to LOGO SCREEN", 140, 220, 20, LIME);
                } break;
                default: break;
            }
        
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}