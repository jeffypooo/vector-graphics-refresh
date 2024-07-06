#include "raylib.h"
#include "rcamera.h"

#define MAX_COLUMNS 15

const char *CameraModeName(int mode);
const char *CameraProjectionName(int proj);
void UpdateCameraMode(Camera *camera, int *mode);
void UpdateCameraProjection(Camera *camera, int *mode);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first-person");

    // Camera init
    Camera3D camera = {
        .position = { 0.0f, 2.0f, 4.0f },
        .target = { 0.0f, 2.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    int cameraMode = CAMERA_FIRST_PERSON;

    // Random columns for game world
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 250), GetRandomValue(10, 55), 30, 255 };
    }

    DisableCursor();

    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------

    // Game loop
    while (!WindowShouldClose()) 
    {
        // Update
        //----------------------------------------------------------------------------------
        // Handle camera mode switching
        UpdateCameraMode(&camera, &cameraMode);
        UpdateCameraProjection(&camera, &cameraMode);
        UpdateCamera(&camera, cameraMode);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw ground
                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY);
                // Draw walls
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);

                // Draw columns
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }

                // Draw player if in third person
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                    DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, PINK);
                }

            EndMode3D();

            float textX = 15.0f;
            float textY = 15.0f;
            DrawText("CAMERA:", textX, textY, 20, RED);
            textX += 15.0f;
            textY += 25.0f;
            DrawText(TextFormat("Mode: %s", CameraModeName(cameraMode)), textX, textY, 15, RED);
            textY += 18.0f;
            DrawText(TextFormat("Projection: %s", CameraProjectionName(camera.projection)), textX, textY, 15, RED);

            DrawFPS(screenWidth - 80.0f, screenHeight - 40.f);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateCameraMode(Camera *camera, int *mode)
{
    // Handle camera mode switching
    // Free Camera
    if (IsKeyPressed(KEY_ONE)) 
    {
        *mode = CAMERA_FREE;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; // reset roll
    }
    // First Person
    if (IsKeyPressed(KEY_TWO)) 
    {
        *mode = CAMERA_FIRST_PERSON;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; // reset roll
    }
    // Third Person
    if (IsKeyPressed(KEY_THREE)) 
    {
        *mode = CAMERA_THIRD_PERSON;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; // reset roll
    }
    // Orbital
    if (IsKeyPressed(KEY_FOUR)) 
    {
        *mode = CAMERA_ORBITAL;
        camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; // reset roll
    }
}

void UpdateCameraProjection(Camera *camera, int *mode)
{
    if (!IsKeyPressed(KEY_P)) return;

    // Update camera projection

    if (camera->projection == CAMERA_PERSPECTIVE) 
    {
        // Switch mode to third person and create isometric view
        *mode = CAMERA_THIRD_PERSON;
        camera->position = (Vector3) { 0.0f, 2.0f, -100.0f };
        camera->target = (Vector3) { 0.0f, 2.0f, 0.0f };
        camera->up = (Vector3) { 0.0f, 1.0f, 0.0f };
        camera->projection = CAMERA_ORTHOGRAPHIC;
        camera->fovy = 20.0f;
        CameraYaw(camera, -135 * DEG2RAD, true);
        CameraPitch(camera, -45 * DEG2RAD, true, true, false);
        return;
    }
    if (camera->projection == CAMERA_ORTHOGRAPHIC)
    {
        // Reset to default view
        *mode = CAMERA_THIRD_PERSON;
        camera->position = (Vector3) { 0.0f, 2.0f, 10.0f };
        camera->target = (Vector3) { 0.0f, 2.0f, 0.0f };
        camera->up = (Vector3) { 0.0f, 1.0f, 0.0f };
        camera->projection = CAMERA_PERSPECTIVE;
        camera->fovy = 60.0f;
        return;
    }
}



const char * CameraModeName(int mode)
{
    switch (mode)
    {
        case CAMERA_FREE: return "Free";
        case CAMERA_FIRST_PERSON: return "First Person";
        case CAMERA_THIRD_PERSON: return "Third Person";
        case CAMERA_ORBITAL: return "Orbital";
        default: return "Unknown";
    }
}

const char * CameraProjectionName(int proj)
{
    switch (proj)
    {
        case CAMERA_PERSPECTIVE: return "Perspective";
        case CAMERA_ORTHOGRAPHIC: return "Orthographic";
        default: return "Unknown";
    }
}