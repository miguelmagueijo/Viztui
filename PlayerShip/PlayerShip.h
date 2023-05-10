//
// Created by migue on 30/04/2023.
//

#ifndef VIZTUI_PLAYERSHIP_H
#define VIZTUI_PLAYERSHIP_H

#include "../Viztui.lib.h"
#include "../Bullet/PlayerBullet.h"

const extern GLfloat playerShipSize[2];
const extern GLfloat playerShipHalfSize[2];

class PlayerShip {
private:
    const static GLshort maxHp = 5;
    PlayerBullet* bullet;

    GLint currentAngle = 0;
    GLfloat position[2]; // X and Y coords
    GLfloat speed;
    GLshort hp;
    GLfloat bulletDmg;


    GLvoid body(GLvoid);
    GLvoid cockpit(GLvoid);
    GLvoid leftWing(GLvoid);
    GLvoid rightWing(GLvoid);
    GLvoid cannon(GLvoid);

public:
    PlayerShip(GLfloat x, GLfloat y, GLfloat speed, GLshort hp);
    ~PlayerShip() = default;

    GLfloat* getPosition(GLvoid);
    GLshort getHp();
    static GLshort getMaxHp();

    GLvoid draw(GLvoid);
    GLboolean move(MOVE_DIRS dir);
    GLvoid receiveHp(GLshort hp);
    GLvoid increaseBulletDmg(GLfloat dmg);
    GLvoid takeDamage(GLshort dmg);
    GLboolean isAlive();
    GLvoid rotate(MOVE_DIRS rDir);
    PlayerBullet* fireBullet();
};


#endif //VIZTUI_PLAYERSHIP_H
