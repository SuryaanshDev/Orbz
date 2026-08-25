#pragma once
#include "raylib.h"

struct Animation{

    Texture2D texture;
    int frameCount;
    float frameDuration;
    bool looping;
};

class Animator {

public:
    Animator();
    void Play(Animation* animation);
    void Update(float dt);
    void Draw(Vector2 position, bool facingRight, float width, float height);
    int GetCurrentFrame() const;
    bool AnimationFinished() const;
    bool IsPlaying(Animation* animation) const;

private:

    Animation* currentAnimation;
    int currentFrame;
    float animationTimer;
    float scale;
    float offsetY;
    bool finished;
};

