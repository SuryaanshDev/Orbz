#include "orb.h"

Orb::Orb(Vector2 startPos, float dir) : rect({startPos.x, startPos.y, 16, 16}), speed(1000.0f), direction(dir)
{
}

void Orb::Update(float dt) {
    
    rect.x += direction * speed * dt;
}

void Orb::Draw() {
    
    DrawCircle(rect.x + rect.width/2, rect.y + rect.height/2, 8, BLUE);
}

Rectangle Orb:: GetRect() const{

    return rect;
}