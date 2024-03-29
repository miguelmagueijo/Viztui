//
// Created by Miguel Magueijo on 07/05/2023.
//

#pragma once
#ifndef VIZTUI_ENEMY_H
#define VIZTUI_ENEMY_H

#include "../Viztui.lib.h"
#include "../Pickup/Pickup.h"

class Enemy {
protected:
    static const GLfloat PRIMARY_COLOR[3];
    static const GLfloat SPECIAL_PRIMARY_COLOR[3];
    static const GLfloat SECONDARY_COLOR[3];
    static const GLfloat COCKPIT_COLOR[3];

    GLfloat position[2] {0.0f, 0.0f }; // initializes position in 0, 0
    GLfloat hp;
    GLboolean hasPickup;
    Pickup* pickup;

public:
    const static GLfloat SIZE[2];
    const static GLfloat HALF_SIZE[2];

    Enemy(GLfloat x, GLfloat y, GLfloat hp);
    ~Enemy() = default;

    GLboolean dropsPickup();
    GLvoid setPickup(Pickup* p);
    Pickup* getPickup();
    GLfloat* getPosition();
    GLvoid takeDamage(GLfloat dmg);
    GLboolean isAlive();
    GLvoid move(MOVE_DIRS dir, GLfloat distance);


    virtual GLvoid draw() = 0;
};


#endif //VIZTUI_ENEMY_H
