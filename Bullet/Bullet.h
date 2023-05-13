//
// Created by Miguel Magueijo on 08/05/2023.
//

#ifndef VIZTUI_BULLET_H
#define VIZTUI_BULLET_H

#include "../Viztui.lib.h"

extern const GLfloat bulletSize[2];
extern const GLfloat bulletHalfSize[2];

class Bullet {
private:
    GLfloat position[2] {0, 0};
    MOVE_DIRS dir;
    GLfloat angle;
    GLfloat speed;
    GLfloat damage;
    GLboolean firedByPlayer;

    GLvoid body();
    GLvoid head();
public:
    Bullet(GLfloat x, GLfloat y, MOVE_DIRS dir, GLboolean firedByPlayer);
    Bullet(GLboolean firedByPlayer);
    ~Bullet() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLvoid setSpeed(GLfloat s);
    GLvoid setDamage(GLfloat d);
    GLvoid setDirection(MOVE_DIRS d);
    GLfloat* getPosition();
    GLfloat getDamage();
    GLboolean damagesPlayer();
    GLvoid move();
    GLvoid draw();
    Bullet* clone();
};


#endif //VIZTUI_BULLET_H
