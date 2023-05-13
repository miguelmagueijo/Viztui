//
// Created by Miguel Magueijo on 09/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUP_H
#define VIZTUI_PICKUP_H

#include "../Viztui.lib.h"
#include "../PlayerShip/PlayerShip.h"

extern const GLfloat pickupSize[2];
extern const GLfloat pickupHalfSize[2];

class Pickup {
protected:
    GLfloat position[2] { 0, 0 };
    MOVE_DIRS dir;
    GLfloat speed;

    GLvoid background();
public:
    Pickup(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);
    Pickup();
    ~Pickup() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLvoid setDirection(MOVE_DIRS d);
    GLvoid setSpeed(GLfloat s);

    GLfloat* getPosition();

    virtual GLvoid move();
    virtual GLvoid draw() = 0;
    virtual GLvoid playerEffect(PlayerShip* playerShip) = 0;
    virtual Pickup* clone() = 0;
};


#endif //VIZTUI_PICKUP_H
