#include "player.h"
#include <algorithm>
#include <iostream>

Player::Player()
: height(32*3), width(32*3), speed(500), gravity(1000),maxJump(2),jumpCount(0), velocity({0, 0}), isGrounded(false),
facingRight(true), isAttacking(false), orbSpawned(false)
{

    idleAnimation.texture         = LoadTexture("assets/player/idle.png");
    idleAnimation.frameCount      = 6;
    idleAnimation.frameDuration   = 0.1f;
    idleAnimation.looping         = true;

    animator.Play(&idleAnimation);

    runAnimation.texture          = LoadTexture("assets/player/running.png");
    runAnimation.frameCount       = 8;
    runAnimation.frameDuration    = 0.1f;
    runAnimation.looping          = true;

    attackAnimation.texture       = LoadTexture("assets/player/attack.png");
    attackAnimation.frameCount    = 10;
    attackAnimation.frameDuration = 0.03;
    attackAnimation.looping       = false;
    
    jumpAnimation.texture         = LoadTexture("assets/player/jump.png");
    jumpAnimation.frameCount      = 6;
    jumpAnimation.frameDuration   = 0.08f;
    jumpAnimation.looping         = true;
}

void Player::Update(std::vector<Rectangle>& platforms) {
    
    float dt = GetFrameTime();
    Move();

    velocity.y += gravity * dt;

    MoveHorizontal(dt);
    ResolveHorizontalCollisions(platforms);

    MoveVertical(dt);
    ResolveVerticalCollisions(platforms);


    //update orbs spawn
    for (auto& orb: orbs) {

        orb.Update(dt);
    }

    orbs.erase(std::remove_if(orbs.begin(), orbs.end(), [](const Orb& orb){return !orb.isActive();}), orbs.end()) ;

    //Animations

    if (isAttacking) {

        animator.Play(&attackAnimation);
    }

    else if(!isGrounded) {

       animator.Play(&jumpAnimation); 
    }

    else if (velocity.x == 0) {

        animator.Play(&idleAnimation);
    }

    else {

        animator.Play(&runAnimation);
    }

    animator.Update(dt);

    if (isAttacking) {

        if (animator.GetCurrentFrame() == 9 && !orbSpawned) {

            Attack();
            orbSpawned = true;
        }

        if (animator.AnimationFinished()) {

            isAttacking = false;
            orbSpawned  = false;
        }
    }
}

void Player::Move() {

    if (isAttacking) {

        velocity.x = 0;
    }

    else {

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
    }

    if (IsKeyPressed(KEY_SPACE) && jumpCount < maxJump) {

        velocity.y = -500;
        isGrounded = false;
        jumpCount++;
    }

    if (IsKeyPressed(KEY_J) && !isAttacking) {

        isAttacking = true;
        orbSpawned  = false;
    }
}

void Player::MoveHorizontal(float dt) {

    position.x += velocity.x * dt;
}

void Player::MoveVertical(float dt) {

    position.y += velocity.y * dt;
}

void Player::Attack() {

    float dir = facingRight? 1.0f : -1.0f;
    Vector2 spawnPos = {position.x + width/2, position.y + height/2};
    orbs.emplace_back(spawnPos, dir);
}

void Player::Draw() {

    DrawRectangleLines(position.x, position.y, width, height, RED);

    animator.Draw(position, facingRight, width, height);    

    for (auto& orb: orbs) {

        orb.Draw();
    }
}

Player::~Player() 
{
    UnloadTexture(idleAnimation.texture);
    UnloadTexture(runAnimation.texture);
    UnloadTexture(attackAnimation.texture);
    UnloadTexture(jumpAnimation.texture);
}

Vector2 Player:: GetPlayerPosition() {

    return position;
}

std::vector<Orb>& Player::GetOrbs() {

    return orbs;
}

void Player::SetPlayerPosition(Vector2 pos) {

    position = pos;
}

Rectangle Player::GetCollider() const {

    return {position.x, position.y, width, height};
}

void Player::ResolveHorizontalCollisions(std::vector<Rectangle>& platforms) {

    Rectangle playerRect = GetCollider();

    for (const auto& platform : platforms) {

        if (!CheckCollisionRecs(playerRect, platform)) {

            continue;
        }

        if (velocity.x > 0) {

            //Moving Right
            float overlap = (playerRect.x + playerRect.width) - platform.x;

            position.x -= overlap;
            velocity.x = 0;
            break;
        }

        else if (velocity.x < 0) {

            //Moving Left
            float overlap = (platform.x + platform.width) - playerRect.x;

            position.x += overlap;
            velocity.x = 0;
            break;
        }
    }
}

void Player::ResolveVerticalCollisions(std::vector<Rectangle>& platforms) {

    Rectangle playerRect = GetCollider();

    isGrounded = false;

    for (const auto& platform : platforms) {

        if (!CheckCollisionRecs(playerRect, platform)) {

            continue;
        }

        if (velocity.y > 0) {

            float overlap = (playerRect.y + playerRect.height) - platform.y;
            position.y -= overlap;
            velocity.y = 0;
            isGrounded = true;
            jumpCount = 0;
            break;
        }

        else if (velocity.y < 0) {

            float overlap = (platform.y + platform.height) - playerRect.y;
            position.y += overlap;
            velocity.y = 0;
            break;
        }
    }
}