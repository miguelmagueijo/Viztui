//
// Created by Miguel Magueijo on 10/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUPMOREDAMAGE_H
#define VIZTUI_PICKUPMOREDAMAGE_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupMoreDamage : public Pickup {
private:
    GLfloat dmgGain;

    GLvoid triangle();
    GLvoid bulletBody();
    GLvoid bulletHead();
public:
    PickupMoreDamage(GLfloat dmgGain);
    ~PickupMoreDamage() = default;

    GLvoid setDamageGain(GLfloat h);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupMoreDamage* clone() override;
};

#endif //VIZTUI_PICKUPMOREDAMAGE_H
