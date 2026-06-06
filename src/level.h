#pragma once
#include "raylib.h"
#include <vector>
#include "enemy.h"
#include <string>
#include <fstream>

class Level {

    private:

        std::vector<Rectangle> platforms;
        std::vector<Enemy> enemies;
        std::vector<std::string> mapData;
        Vector2 playerSpawn;

    public:

        Level();
        void Update();
        void Draw();

        std::vector<Rectangle>& GetPlatforms();
        std::vector<Enemy>& GetEnemies();
        Vector2 GetPlayerSpawn() const;
};