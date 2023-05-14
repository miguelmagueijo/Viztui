//
// Created by migue on 30/04/2023.
//

#pragma once
#ifndef VIZTUI_PLAYERSHIP_H
#define VIZTUI_PLAYERSHIP_H

#include "../Viztui.lib.h"
#include "../Bullet/Bullet.h"

const extern GLfloat playerShipSize[2];
const extern GLfloat playerShipHalfSize[2];

class PlayerShip {
private:
    const static GLfloat PRIMARY_COLOR[3];
    const static GLfloat SECONDARY_COLOR[3];
    const static GLfloat COCKPIT_COLOR[3];

    const static GLfloat bulletSpace;

    const static GLshort maxHp = 5;
    Bullet* bullet;

    GLint currentAngle = 0;
    GLfloat position[2]; // X and Y coords
    GLfloat speed;
    GLshort hp;
    GLfloat bulletDmg;
    GLboolean canFireExtra;


    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid leftWing(GLvoid);
    GLvoid rightWing(GLvoid);
    GLvoid cannon(GLvoid);

public:
    PlayerShip(GLfloat x, GLfloat y, GLfloat speed, GLshort hp);
    ~PlayerShip() = default;

    GLvoid setFireExtra(GLboolean fExtra);
    GLfloat* getPosition();
    GLshort getHp();
    static GLshort getMaxHp();

    GLvoid draw();
    GLboolean move(MOVE_DIRS dir);
    GLvoid receiveHp(GLshort hp);
    GLvoid increaseBulletDmg(GLfloat dmg);
    GLvoid takeDamage(GLshort dmg);
    GLboolean isAlive();
    GLvoid rotate(MOVE_DIRS rDir);
    std::vector<Bullet*> fireBullet();
};


#endif //VIZTUI_PLAYERSHIP_H
