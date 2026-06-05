#pragma once
#include "raylib.h"
#include <vector>
#include "enemy.h"

class Level {

    private:

        std::vector<Rectangle> platforms;
        std::vector<Enemy> enemies;

    public:

        Level();
        void Update();
        void Draw();

        std::vector<Rectangle>& GetPlatforms();
        std::vector<Enemy>& GetEnemies();
};