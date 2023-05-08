//
// Created by Miguel Magueijo on 08/05/2023.
//

#ifndef VIZTUI_ENEMYBULLET_H
#define VIZTUI_ENEMYBULLET_H

#include "../Viztui.lib.h"
#include "Bullet.h"

class EnemyBullet : public Bullet {
private:
    GLvoid body();
    GLvoid head();
public:
    EnemyBullet(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed, GLfloat dmg);
    ~EnemyBullet() = default;

    GLvoid draw() override;
    EnemyBullet* clone() override;
};


#endif //VIZTUI_ENEMYBULLET_H
