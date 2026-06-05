#pragma once
#include "raylib.h"

class Orb {

    public:
        Orb(Vector2 startPos, float direction);
        
        void Update(float dt);
        void Draw();
        Rectangle GetRect() const;
        void Destroy();
        bool isActive() const;

    private:

        Rectangle rect;
        float orbSpeed;
        float distanceTravelled;
        float maxDistance;
        float speed;
        float direction;
        bool active;
};