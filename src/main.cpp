#include "player.h"
int main() 
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "Platformer");
    SetTargetFPS(120);
    
    Player player;
    Rectangle rect = {0, 900, 10000, 500}; 
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f};

    float damping = 0.1f;

    while (!WindowShouldClose())
    {

        player.Update(rect);
        camera.target.x += (player.GetPlayerPosition().x - camera.target.x) * damping;
        camera.target.y += (player.GetPlayerPosition().y - 200 - camera.target.y) * damping;
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                DrawRectangleRec(rect, GREEN);
                player.Draw();   
            EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
}