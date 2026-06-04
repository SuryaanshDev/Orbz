#pragma once
#include "raylib.h"

class Enemy {

    public:

        Enemy(float x, float y);
        void Draw();
        Rectangle GetRect() const;
        bool isAlive() const;
        void Kill();

    private:

        Rectangle rect;
        bool alive;
};