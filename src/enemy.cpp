#include "enemy.h"

Enemy::Enemy(float x, float y): rect({x, y, 80, 70}), alive(true)  
{
}

void Enemy::Draw() {
    
    if (alive) {
        DrawRectangleRec(rect, BLUE);
    }
}

Rectangle Enemy::GetRect() const {

    return rect;
}

void Enemy::Kill() {

    alive = false;
}

bool Enemy::isAlive() const {
    return alive;
}

