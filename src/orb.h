#pragma once
#include "raylib.h"

class Orb {

    public:
        Orb(Vector2 startPos, float direction);
        
        void Update(float dt);
        void Draw();
        Rectangle GetRect() const;

    private:

        float orbSpeed;
        Rectangle rect;
        float speed;
        float direction;
};