#include "orb.h"
#include <math.h>

Orb::Orb(Vector2 startPos, float dir) : rect({startPos.x, startPos.y, 16, 16}), distanceTravelled(0), maxDistance(800),
speed(1000.0f), direction(dir), active(true)
{
}

void Orb::Update(float dt) {
    
    if (!active) return;

    float movement = direction * speed * dt;    
    rect.x += movement;

    distanceTravelled += std::abs(movement);

    if (distanceTravelled > maxDistance) {

        Destroy();
    }
}

void Orb::Draw() {
    
    if (!active) return;

    DrawCircle(rect.x + rect.width/2, rect.y + rect.height/2, 8, BLUE);
}

Rectangle Orb:: GetRect() const{

    return rect;
}

void Orb::Destroy() {

    active = false;
}

bool Orb::isActive() const{

    return active;
}