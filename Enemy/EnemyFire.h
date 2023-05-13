//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_ENEMYFIRE_H
#define VIZTUI_ENEMYFIRE_H


#include "../Viztui.lib.h"
#include "Enemy.h"

class EnemyFire : public Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid cannon();
    GLvoid leftWing();
    GLvoid rightWing();

public:
    EnemyFire(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~EnemyFire() = default;

    GLvoid draw() override;
};


#endif //VIZTUI_ENEMYFIRE_H
