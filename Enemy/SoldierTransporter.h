//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_SOLDIERTRANSPORTER_H
#define VIZTUI_SOLDIERTRANSPORTER_H

#include "../Viztui.lib.h"

extern GLfloat soldierTransporterSize[2];

class SoldierTransporter {
private:
    GLfloat position[2] {0.0f, 0.0f};
    GLfloat speed;
    GLfloat hp;

    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid rocket(GLvoid);

public:
    SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    SoldierTransporter(GLvoid);
    SoldierTransporter(GLfloat x, GLfloat y);
    SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed);

    GLvoid draw(GLvoid);
    GLvoid move(MOVE_DIRECTIONS dir);
    GLfloat* getPosition(GLvoid);
    GLvoid takeDamage(GLfloat);
    GLboolean isAlive(GLvoid);
};


#endif //VIZTUI_SOLDIERTRANSPORTER_H
