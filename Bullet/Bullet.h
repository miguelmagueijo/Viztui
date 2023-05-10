//
// Created by Miguel Magueijo on 08/05/2023.
//

#ifndef VIZTUI_BULLET_H
#define VIZTUI_BULLET_H

#include "../Viztui.lib.h"

class Bullet {
protected:
    GLfloat position[2] {0, 0};
    MOVE_DIRS dir;
    GLfloat angle;
    GLfloat speed;
    GLfloat damage;
public:
    Bullet(GLfloat x, GLfloat y, MOVE_DIRS dir);
    Bullet();
    ~Bullet() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLvoid setSpeed(GLfloat s);
    GLvoid setDamage(GLfloat d);
    GLvoid setDirection(MOVE_DIRS d);
    GLfloat* getPosition();
    GLfloat getDamage();
    virtual GLboolean damagesPlayer();
    GLvoid move();

    virtual GLvoid draw() = 0;
    virtual Bullet* clone() = 0;
};


#endif //VIZTUI_BULLET_H
