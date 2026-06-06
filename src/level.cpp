#include "level.h"
#include <iostream>

Level::Level() 

{
    std::cout << "Level constructor running...\n";
    std::ifstream file("assets/levels/level1.txt");

    if (file.is_open()) {

        std::cout << "file opened...\n";
    }

    else {
        std::cout << "failed to open...\n";
    }

    std::string line;

    while(std::getline(file, line)) {

        mapData.push_back(line);
    }

    const int tileSize = 64;

    for (size_t row = 0; row < mapData.size(); row++) {

        for (size_t col = 0; col < mapData[row].size(); col++) {

            char tile = mapData[row][col];
            float x = col * tileSize;
            float y = row * tileSize;

            switch(tile)
            {

                case 'X' :
                {
                    platforms.push_back({x, y, (float)tileSize, (float)tileSize});
                    break;
                }

                case 'E' :
                {

                    enemies.emplace_back(x, y);
                    break;
                }

                case 'P' :
                {

                    playerSpawn = {x, y};
                    break;
                }
            }
        }
    } 
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

Vector2 Level::GetPlayerSpawn() const {

    return playerSpawn;
}