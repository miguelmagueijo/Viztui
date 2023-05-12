//
// Created by Miguel Magueijo on 07/05/2023.
//

#ifndef VIZTUI_ENEMY_H
#define VIZTUI_ENEMY_H

#include "../Viztui.lib.h"
#include "../Pickup/Pickup.h"

class Enemy {
protected:
    GLfloat position[2] {0.0f, 0.0f }; // initializes position in 0, 0
    GLfloat speed;
    GLfloat hp;
    GLboolean hasPickup;
    Pickup* pickup;

public:
    static constexpr GLfloat size[2] { 20,  10};

    Enemy(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~Enemy() = default;

    GLboolean dropsPickup();
    GLvoid setPickup(Pickup* p);
    Pickup* getPickup();
    GLfloat* getPosition();
    GLvoid takeDamage(GLfloat dmg);
    GLboolean isAlive();
    GLvoid move(MOVE_DIRS dir);


    virtual GLvoid draw() = 0;
};


#endif //VIZTUI_ENEMY_H
