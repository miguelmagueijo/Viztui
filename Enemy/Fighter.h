//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_FIGHTER_H
#define VIZTUI_FIGHTER_H


#include "../Viztui.lib.h"
#include "Enemy.h"

class Fighter : public Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid cannon();
    GLvoid leftWing();
    GLvoid rightWing();

public:
    Fighter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~Fighter() = default;

    GLvoid draw() override;
};


#endif //VIZTUI_FIGHTER_H
