//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_SOLDIERTRANSPORTER_H
#define VIZTUI_SOLDIERTRANSPORTER_H

#include "../Viztui.lib.h"
#include "Enemy.h"

class SoldierTransporter : public Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid rocket();

public:
    SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~SoldierTransporter() = default;

    GLvoid draw();
};


#endif //VIZTUI_SOLDIERTRANSPORTER_H
