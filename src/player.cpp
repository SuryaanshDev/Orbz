#include "player.h"

Player::Player()
: height(80), width(70), speed(500), gravity(1000),maxJump(2),jumpCount(0), position({100, 600}), velocity({0, 0}), isGrounded(false),
facingRight(true)
{
}

void Player::Update(Rectangle ground) {
    
    float dt = GetFrameTime();
    Player::Move();

    //Collision
    Rectangle playerRect = {position.x, position.y, width, height};

    if (CheckCollisionRecs(playerRect, ground)) {

        position.y = ground.y - height;
        velocity.y = 0;
        isGrounded = true;
        jumpCount = 0;
    }

    else {

        isGrounded = false;
    }

    //update orbs spawn
    for (auto& orb: orbs) {

        orb.Update(dt);
    }
}

void Player::Move() {
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_D)) {

        velocity.x = speed;
        facingRight = true;
    }

    else if (IsKeyDown(KEY_A)) {

        velocity.x = -speed;
        facingRight = false;
    }

    else {

        velocity.x = 0;
    }

    velocity.y += gravity * dt;

    if (IsKeyPressed(KEY_SPACE) && jumpCount < maxJump) {

        velocity.y = -500;
        isGrounded = false;
        jumpCount++;
    }

    if (IsKeyPressed(KEY_J)) {

        Attack();
    }

// Final velocities for player movement
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Player::Attack() {

    float dir = facingRight? 1.0f : -1.0f;
    Vector2 spawnPos = {position.x + width/2, position.y + height/2};
    orbs.emplace_back(spawnPos, dir);
}

void Player::Draw() {
    
    Rectangle rect = {position.x, position.y, width, height};
    DrawRectangleRec(rect, RED);

    for (auto& orb: orbs) {

        orb.Draw();
    }
}

Vector2 Player:: GetPlayerPosition() {

    return position;
}

std::vector<Orb>& Player::GetOrbs() {

    return orbs;
}