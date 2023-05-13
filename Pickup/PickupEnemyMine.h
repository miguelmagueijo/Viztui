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
    GLint damage;

    GLvoid body();
    GLvoid plate();
public:
    PickupEnemyMine(GLint dmg);
    ~PickupEnemyMine() = default;

    GLvoid setDamage(GLint d);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupEnemyMine* clone() override;
};


#endif //VIZTUI_PICKUPENEMYMINE_H
