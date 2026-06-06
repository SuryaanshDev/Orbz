#include "player.h"
#include "enemy.h"
#include "orb.h"
#include "level.h"

int main() 
{
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "Platformer");
    SetTargetFPS(120);
    
    Player player;
    Level level;

    player.SetPlayerPosition(level.GetPlayerSpawn());
    //Rectangle ground = {0, 900, 10000, 500}; 
    Camera2D camera = {0};
    camera.zoom = 1.0f;
    
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f};

    float damping = 0.1f;

    while (!WindowShouldClose())
    {

        player.Update(level.GetPlatforms());
        camera.target.x += (player.GetPlayerPosition().x - camera.target.x) * damping;
        camera.target.y += (player.GetPlayerPosition().y - 200 - camera.target.y) * damping;
        
        //Checking for collisions
        for (auto& enemy : level.GetEnemies()) {

            for (auto& orb : player.GetOrbs()) {

                if (enemy.isAlive() && CheckCollisionRecs(orb.GetRect(), enemy.GetRect())) {

                    enemy.Kill();
                    orb.Destroy();
                }
            }
        } 

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                //DrawRectangleRec(ground, GREEN);
                level.Draw();
                player.Draw();   
            EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
}