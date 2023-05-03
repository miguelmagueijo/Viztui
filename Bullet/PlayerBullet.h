//
// Created by Miguel Magueijo on 02/05/2023.
//

#ifndef VIZTUI_PLAYERBULLET_H
#define VIZTUI_PLAYERBULLET_H

#include "../Viztui.lib.h"

extern GLfloat playerBulletSize[2];

class PlayerBullet {
private:
    GLfloat position[2];
    GLfloat speed;
    GLfloat damage;

    GLvoid body(GLvoid);
    GLvoid head(GLvoid);
public:
    PlayerBullet();
    PlayerBullet(GLfloat, GLfloat);
    PlayerBullet(GLfloat, GLfloat, GLfloat);
    PlayerBullet(GLfloat, GLfloat, GLfloat, GLfloat);
    ~PlayerBullet();
    GLvoid draw(GLvoid);
    GLvoid move(GLint);
    GLfloat* getPosition(GLvoid);
};


#endif //VIZTUI_PLAYERBULLET_H
