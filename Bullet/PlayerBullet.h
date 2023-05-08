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
    PlayerBullet(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed, GLfloat dmg);
    ~PlayerBullet() = default;

    GLvoid draw() override;
    PlayerBullet* clone() override;
};


#endif //VIZTUI_PLAYERBULLET_H
