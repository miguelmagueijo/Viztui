//
// Created by Miguel Magueijo on 02/05/2023.
//

#ifndef VIZTUI_PLAYERBULLET_H
#define VIZTUI_PLAYERBULLET_H

#include "../Viztui.lib.h"
#include "Bullet.h"

class PlayerBullet : public Bullet {
private:
    GLvoid body();
    GLvoid head();
public:
    PlayerBullet(GLfloat x, GLfloat y, MOVE_DIRS dir);
    PlayerBullet();
    ~PlayerBullet() = default;

    GLboolean damagesPlayer() override;
    GLvoid draw() override;
    PlayerBullet* clone() override;
};


#endif //VIZTUI_PLAYERBULLET_H
