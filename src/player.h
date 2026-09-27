#pragma once
#include <vector>
#include "raylib.h"
#include "orb.h"
#include "animator.h"

class Player {
private: 

    Animator animator;

    //Animations
    Animation idleAnimation;
    Animation runAnimation;
    Animation attackAnimation;
    Animation jumpAnimation;

public:

    Player();
    ~Player();
    void Update(std::vector<Rectangle>& platforms);
    void Draw();
    std::vector<Orb>& GetOrbs();

public:
 
    Vector2 GetPlayerPosition();
    void SetPlayerPosition(Vector2 pos);
    
private:

    void Move();
    void MoveHorizontal(float dt);
    void MoveVertical(float dt);
    void Attack();
    
    void ResolveHorizontalCollisions(std::vector<Rectangle>& platforms);
    void ResolveVerticalCollisions(std::vector<Rectangle>& platforms);

    Rectangle GetCollider() const;
private:

    float height;
    float width;
    float speed;
    float gravity;

    int maxJump;
    int jumpCount;
    
    Vector2 position;
    Vector2 velocity;

    std::vector<Orb> orbs;
    
    bool isGrounded;
    bool facingRight;
    
    bool isAttacking;
    bool orbSpawned;
};