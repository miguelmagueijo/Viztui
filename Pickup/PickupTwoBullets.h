//
// Created by Miguel Magueijo on 11/05/2023.
//

#ifndef VIZTUI_PICKUPTWOBULLETS_H
#define VIZTUI_PICKUPTWOBULLETS_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupTwoBullets : public Pickup {
private:
    static GLfloat size[2];
    static GLfloat halfSize[2];

    GLvoid bulletBody();
    GLvoid bulletHead();
public:
    PickupTwoBullets(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);
    PickupTwoBullets(MOVE_DIRS dir, GLfloat speed);
    ~PickupTwoBullets() = default;

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    Pickup* clone() override;
};


#endif //VIZTUI_PICKUPTWOBULLETS_H
