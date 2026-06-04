#include "player.h"
#include "enemy.h"
#include "orb.h"

int main() 
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "Platformer");
    SetTargetFPS(120);
    
    Player player;
    Enemy enemy(1200, 830);
    Rectangle ground = {0, 900, 10000, 500}; 
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f};

    float damping = 0.1f;

    while (!WindowShouldClose())
    {

        player.Update(ground);
        camera.target.x += (player.GetPlayerPosition().x - camera.target.x) * damping;
        camera.target.y += (player.GetPlayerPosition().y - 200 - camera.target.y) * damping;
        
        for (auto& orbs : player.GetOrbs()) {

            if (enemy.isAlive() && CheckCollisionRecs(enemy.GetRect(), orbs.GetRect())) {

                enemy.Kill();
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                DrawRectangleRec(ground, GREEN);
                player.Draw();   
                enemy.Draw();
            EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
}