//
// Created by Miguel Magueijo on 04/05/2023.
//

#ifndef VIZTUI_MINETRANSPORTER_H
#define VIZTUI_MINETRANSPORTER_H

#include "../Viztui.lib.h"

extern GLfloat mineTransporterSize[2];

class MineTransporter {
private:
    GLfloat position[2] {0.0f, 0.0f};
    GLfloat speed;
    GLfloat hp;

    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid wing(GLvoid);
    GLvoid mine(GLvoid);

public:
    MineTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    MineTransporter(GLvoid);
    MineTransporter(GLfloat x, GLfloat y);
    MineTransporter(GLfloat x, GLfloat y, GLfloat speed);

    GLvoid draw(GLvoid);
    GLvoid move(MOVE_DIRECTIONS dir);
    GLfloat* getPosition(GLvoid);
    GLvoid takeDamage(GLfloat);
    GLboolean isAlive(GLvoid);
};


#endif //VIZTUI_MINETRANSPORTER_H
