//
// Created by migue on 30/04/2023.
//

#ifndef VIZTUI_PLAYERSHIP_H
#define VIZTUI_PLAYERSHIP_H

#include "../Viztui.lib.h"

extern GLfloat playerShipSize[2];

class PlayerShip {
private:
    GLfloat position[2]; // X and Y coords
    GLfloat speed;
    GLint lives;

    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid leftWing(GLvoid);
    GLvoid rightWing(GLvoid);
    GLvoid cannon(GLvoid);

public:
    PlayerShip();
    PlayerShip(GLfloat x, GLfloat y);
    PlayerShip(GLfloat x, GLfloat y, GLfloat speed);
    PlayerShip(GLfloat x, GLfloat y, GLint lives);
    PlayerShip(GLfloat x, GLfloat y, GLfloat speed, GLint lives);
    ~PlayerShip();
    GLvoid draw(GLvoid);
    GLvoid move(GLint);
    GLfloat* getPosition(GLvoid);
};


#endif //VIZTUI_PLAYERSHIP_H
