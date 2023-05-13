//
// Created by Miguel Magueijo on 04/05/2023.
//

#pragma once
#ifndef VIZTUI_ENEMYMINER_H
#define VIZTUI_ENEMYMINER_H

#include "../Viztui.lib.h"
#include "Enemy.h"
#include "../Pickup/PickupEnemyMine.h"

class EnemyMiner : public Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid wing();
    GLvoid mine();

public:
    EnemyMiner(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~EnemyMiner() = default;

    GLvoid draw() override;
};


#endif //VIZTUI_ENEMYMINER_H
