//
// Created by Miguel Magueijo on 10/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUPMOREHP_H
#define VIZTUI_PICKUPMOREHP_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupMoreHp : public Pickup {
private:
    GLint hpGain;

    GLvoid leftArcTriangle();
    GLvoid rightArcTriangle();
    GLvoid bottomTriangle();
    GLvoid rectVertical();
    GLvoid rectHorizontal();
public:
    PickupMoreHp(GLint hpGain);
    ~PickupMoreHp() = default;

    GLvoid setHpGain(GLint h);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupMoreHp* clone() override;
};


#endif //VIZTUI_PICKUPMOREHP_H
