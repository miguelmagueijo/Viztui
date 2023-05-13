//
// Created by Miguel Magueijo on 09/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUPENEMYMINE_H
#define VIZTUI_PICKUPENEMYMINE_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupEnemyMine : public Pickup {
private:
    static GLfloat size[2];
    static GLfloat halfSize[2];

    GLshort damage;

    GLvoid body();
    GLvoid plate();
public:
    PickupEnemyMine(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);
    ~PickupEnemyMine() = default;

    GLvoid setDamage(GLshort d);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupEnemyMine* clone() override;
};


#endif //VIZTUI_PICKUPENEMYMINE_H
