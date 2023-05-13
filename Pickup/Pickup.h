//
// Created by Miguel Magueijo on 09/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUP_H
#define VIZTUI_PICKUP_H

#include "../Viztui.lib.h"
#include "../PlayerShip/PlayerShip.h"

class Pickup {
protected:
    GLfloat position[2];
    MOVE_DIRS dir;
    GLfloat speed;
public:
    Pickup(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);\
    Pickup(MOVE_DIRS dir, GLfloat speed);
    ~Pickup() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLfloat* getPosition();

    GLvoid move();
    virtual GLvoid draw() = 0;
    virtual GLvoid playerEffect(PlayerShip* playerShip) = 0;
    virtual Pickup* clone() = 0;
};


#endif //VIZTUI_PICKUP_H
