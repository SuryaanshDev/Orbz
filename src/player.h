#pragma once
#include <vector>
#include "raylib.h"
#include "orb.h"

class Player {

public:

    Player();
    
    void Update(std::vector<Rectangle>& platforms);
    void Draw();
    std::vector<Orb>& GetOrbs();

public:
 
    Vector2 GetPlayerPosition();
    void SetPlayerPosition(Vector2 pos);
private:

    void Move();
    void Attack();

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
};