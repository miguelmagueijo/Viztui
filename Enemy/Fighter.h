//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_FIGHTER_H
#define VIZTUI_FIGHTER_H


#include "../Viztui.lib.h"

extern GLfloat fighterSize[2];

class Fighter {
private:
    GLfloat position[2] {0.0f, 0.0f};
    GLfloat speed;
    GLfloat hp;

    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid cannon(GLvoid);
    GLvoid leftWing(GLvoid);
    GLvoid rightWing(GLvoid);

public:
    Fighter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    Fighter(GLvoid);
    Fighter(GLfloat x, GLfloat y);
    Fighter(GLfloat x, GLfloat y, GLfloat speed);
    ~Fighter();

    GLvoid draw(GLvoid);
    GLvoid move(MOVE_DIRECTIONS dir);
    GLfloat* getPosition(GLvoid);
    GLvoid takeDamage(GLfloat);
    GLboolean isAlive(GLvoid);
};


#endif //VIZTUI_FIGHTER_H
