#include "level.h"

Level::Level() {

    platforms.push_back({0, 900, 10000, 500});

    //Floating platforms
    platforms.push_back({600, 700, 300, 40});
    platforms.push_back({1200, 500, 300, 40});

    //Spawning enemies
    enemies.emplace_back(730, 630);
    enemies.emplace_back(1300, 430);
}

void Level::Draw() {

    for (auto& platform: platforms) {

        DrawRectangleRec(platform, GREEN);
    }

    for (auto& enemy: enemies) {

        enemy.Draw();
    }
}

std::vector<Rectangle>& Level::GetPlatforms() {

    return platforms;
}

std::vector<Enemy>& Level::GetEnemies() {

    return enemies;
}