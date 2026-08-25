#include "animator.h"

Animator::Animator() {

    currentAnimation = nullptr;
    currentFrame     = 0;
    animationTimer   = 0.0f;
    scale            = 4.0f;
    offsetY          = 18.0f;
    finished         = false;
}

void Animator::Play(Animation* animation) {

    if (currentAnimation != animation) {

        currentAnimation = animation;
        currentFrame     = 0;
        animationTimer   = 0.0f;
        finished         = false;
    }
}

void Animator::Update(float dt) {

    if (currentAnimation == nullptr) {
        return;
    }    

    animationTimer += dt;

    if (animationTimer >= currentAnimation->frameDuration) {
        animationTimer = 0.0f;
        currentFrame++;

        if (currentFrame >= currentAnimation->frameCount) {
            if (currentAnimation->looping) {
                currentFrame = 0;
            }
            else {
                currentFrame = currentAnimation->frameCount - 1;
                finished = true;
            }
        }
    }
}

void Animator::Draw(Vector2 position, bool facingRight, float width, float height) {

    if (currentAnimation == nullptr) {

        return;
    }

    int frameWidth = currentAnimation->texture.width / currentAnimation->frameCount;
    int frameHeight = currentAnimation->texture.height;

    Rectangle source;

    if (facingRight) {

        source = {(float)(currentFrame*frameWidth), 0, (float)frameWidth, (float)frameHeight};
    } 

    else {

        source = {(float)(currentFrame*frameWidth), 0, -(float)frameWidth, (float)frameHeight};
    }

    Rectangle dest = {position.x + (width - frameWidth * scale)/2.0f, position.y + (height - frameHeight * scale) + offsetY,
                      (float)frameWidth * scale, (float)frameHeight * scale};

    DrawTexturePro(currentAnimation->texture, source, dest, {0, 0}, 0.0f, WHITE);
}

int Animator::GetCurrentFrame() const {

    return currentFrame;
}

bool Animator::AnimationFinished() const {
   
    return finished;
}

bool Animator::IsPlaying(Animation* animation) const {

    return currentAnimation == animation;
}