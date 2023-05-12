//
// Created by Miguel Magueijo on 10/05/2023.
//

#ifndef VIZTUI_PICKUPMOREDAMAGE_H
#define VIZTUI_PICKUPMOREDAMAGE_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupMoreDamage : public Pickup {
private:
    static GLfloat size[2];
    static GLfloat halfSize[2];

    GLshort dmgGain;

    GLvoid triangle();
    GLvoid bulletBody();
    GLvoid bulletHead();
public:
    PickupMoreDamage(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);
    PickupMoreDamage(MOVE_DIRS dir, GLfloat speed);
    ~PickupMoreDamage() = default;

    GLvoid setDamageGain(GLshort h);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupMoreDamage* clone() override;
};

#endif //VIZTUI_PICKUPMOREDAMAGE_H
