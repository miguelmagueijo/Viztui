//
// Created by Miguel Magueijo on 11/05/2023.
//

#pragma once
#ifndef VIZTUI_PICKUPTWOBULLETS_H
#define VIZTUI_PICKUPTWOBULLETS_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupTwoBullets : public Pickup {
private:
    GLvoid bulletBody();
    GLvoid bulletHead();
public:
    PickupTwoBullets();
    ~PickupTwoBullets() = default;

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    Pickup* clone() override;
};


#endif //VIZTUI_PICKUPTWOBULLETS_H
