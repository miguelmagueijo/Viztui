//
// Created by Miguel Magueijo on 08/05/2023.
//

#ifndef VIZTUI_BULLET_H
#define VIZTUI_BULLET_H

#include "../Viztui.lib.h"

class Bullet {
protected:
    GLfloat position[2] {0, 0};
    GLboolean firedByPlayer; // if true cannot damage player, if false can damage player
    MOVE_DIRS dir;
    GLfloat speed = 0;
    GLfloat damage = 0;
public:
    Bullet(GLfloat x, GLfloat y, GLboolean firedByPlayer, MOVE_DIRS dir);
    Bullet();
    ~Bullet() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLvoid setSpeed(GLfloat s);
    GLvoid setDamage(GLfloat d);
    GLvoid setDirection(MOVE_DIRS d);
    GLfloat* getPosition();
    GLfloat getDamage();
    GLboolean isFiredByPlayer();

    GLvoid move();

    virtual GLvoid draw() = 0;
    virtual Bullet* clone() = 0;
};


#endif //VIZTUI_BULLET_H
