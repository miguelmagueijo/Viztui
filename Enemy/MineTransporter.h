//
// Created by Miguel Magueijo on 04/05/2023.
//

#ifndef VIZTUI_MINETRANSPORTER_H
#define VIZTUI_MINETRANSPORTER_H

#include "../Viztui.lib.h"
#include "Enemy.h"

class MineTransporter : Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid wing();
    GLvoid mine();

public:
    MineTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~MineTransporter() = default;

    GLvoid draw() override;
};


#endif //VIZTUI_MINETRANSPORTER_H
