//
// Created by Miguel Magueijo on 02/05/2023.
//

#ifndef VIZTUI_PLAYERBULLET_H
#define VIZTUI_PLAYERBULLET_H

#include "../Viztui.lib.h"

extern GLfloat playerBulletSize[2];

class PlayerBullet {
private:
    GLfloat position[2] {0, 0};
    GLfloat speed;
    GLfloat damage;
    MOVE_DIRS dir;

    GLvoid body();
    GLvoid head();
public:
    PlayerBullet(GLfloat x, GLfloat y, GLfloat speed, GLfloat dmg, MOVE_DIRS dir);
    PlayerBullet();
    ~PlayerBullet() = default;

    GLvoid setPosition(GLfloat x, GLfloat y);
    GLfloat* getPosition();
    GLfloat getDamage();

    GLvoid draw();
    GLvoid move();

    PlayerBullet* clone();
};


#endif //VIZTUI_PLAYERBULLET_H
