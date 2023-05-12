//
// Created by Miguel Magueijo on 10/05/2023.
//

#ifndef VIZTUI_PICKUPMOREHP_H
#define VIZTUI_PICKUPMOREHP_H

#include "../Viztui.lib.h"
#include "Pickup.h"

class PickupMoreHp : public Pickup {
private:
    static GLfloat size[2];
    static GLfloat halfSize[2];

    GLshort hpGain;

    GLvoid leftArcTriangle();
    GLvoid rightArcTriangle();
    GLvoid bottomTriangle();
    GLvoid rectVertical();
    GLvoid rectHorizontal();
public:
    PickupMoreHp(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed);
    PickupMoreHp(MOVE_DIRS dir, GLfloat speed);
    ~PickupMoreHp() = default;

    GLvoid setHpGain(GLshort h);

    GLvoid draw() override;
    GLvoid playerEffect(PlayerShip* playerShip) override;
    PickupMoreHp* clone() override;
};


#endif //VIZTUI_PICKUPMOREHP_H
