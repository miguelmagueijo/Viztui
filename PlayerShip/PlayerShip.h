//
// Created by migue on 30/04/2023.
//

#ifndef VIZTUI_PLAYERSHIP_H
#define VIZTUI_PLAYERSHIP_H

#include "../Viztui.lib.h"

const extern GLfloat playerShipSize[2];
const extern GLfloat playerShipHalfSize[2];

class PlayerShip {
private:
    const static GLint maxHp = 5;

    GLint currentAngle = 0;
    GLfloat position[2]; // X and Y coords
    GLfloat speed;
    GLint hp;


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
    PlayerShip(GLfloat x, GLfloat y, GLfloat speed, GLint hp);
    ~PlayerShip();
    GLvoid draw(GLvoid);
    GLboolean move(MOVE_DIRS dir);
    GLvoid receiveHp(GLint hp);
    GLvoid takeDamage(GLint dmg);
    GLboolean isAlive();
    GLfloat* getPosition(GLvoid);
    GLvoid rotate(GLboolean isCW);
};


#endif //VIZTUI_PLAYERSHIP_H
