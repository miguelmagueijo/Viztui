//
// Created by migue on 30/04/2023.
//

#include "PlayerShip.h"

// Size ratio is 40:30 (4:3)
GLfloat playerShipSize[2] = { 30.0f, 22.5f };

PlayerShip::PlayerShip() {
    this->speed = 1.5f;
}

PlayerShip::PlayerShip(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = 1.5f;
}

GLvoid PlayerShip::body(GLvoid) {
    glColor3f(0.77f, 0.61f, 0.19f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] / 4.0f, playerShipSize[1]);
        glVertex2f(playerShipSize[0] / 2.0f, 0);
    } glEnd();
}

GLvoid PlayerShip::cockpit(GLvoid) {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] * 0.1f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] * 0.3f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] / 10.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::leftWing(GLvoid) {
    glColor3f(0.0, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(playerShipSize[0] / 2.0f, 0.0f);
        glVertex2f(0, playerShipSize[1] / 2.0f);
        glVertex2f(playerShipSize[0] / 2.0f, playerShipSize[1] / 2.0f);
    } glEnd();
}

GLvoid PlayerShip::rightWing(GLvoid) {
    glColor3f(0.0, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0, playerShipSize[1] / 2.0f);
        glVertex2f(playerShipSize[0] / 2.0f, playerShipSize[1] / 2.0f);
    } glEnd();
}

GLvoid PlayerShip::cannon(GLvoid) {
    glColor3f(0.77f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] * 0.1f / 4.0f, playerShipSize[1] / 10.0f);
        glVertex2f(playerShipSize[0] * 0.3f / 4.0f, playerShipSize[1] / 10.0f);
        glVertex2f(playerShipSize[0] / 10.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Translation for body component / center of ship
    glTranslatef(this->position[0] - playerShipSize[0] / 4.0f, this->position[1] - playerShipSize[1] / 2.0f, 0.0f);
    glPushMatrix();

    // Left wing translation and draw
    glTranslatef(-(playerShipSize[0] / 4.0f), 0.0f, 0.0f);
    this->leftWing();

    // Pop current matrix and create new one
    glPopMatrix();
    glPushMatrix();

    // Right wing translation and draw
    glTranslatef(playerShipSize[0] / 4.0f, 0.0f, 0.0f);
    this->rightWing();

    // Pop current matrix and create new one
    glPopMatrix();
    glPushMatrix();

    // Body drawn, it's here because of wings overlapping if they are drawn after body
    this->body();

    // Pop current matrix and create new one
    glPopMatrix();
    glPushMatrix();

    glTranslatef(playerShipSize[0] / 5.0f, playerShipSize[1] * 1.1f / 3.0f, 0.0f);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(-(playerShipSize[0] * 0.1f / 4.0f), playerShipSize[1] / 2.0f, 0.0f);
    this->cannon();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(playerShipSize[0] * 1.7f / 4.0f, playerShipSize[1] / 2.0f, 0.0f);
    this->cannon();

    glPopMatrix();
    glPopMatrix();
}

GLboolean PlayerShip::move(MOVE_DIRECTIONS dir) {
    GLboolean hasMoved = false;

    switch(dir) {
        case MOVE_DIRECTIONS::UP:
            this->position[1] += this->speed;
            break;
        case MOVE_DIRECTIONS::DOWN:
            this->position[1] -= this->speed;
            break;
        case MOVE_DIRECTIONS::LEFT:
            this->position[0] -= this->speed;
            break;
        case MOVE_DIRECTIONS::RIGHT:
            this->position[0] += this->speed;
            break;
    }

    return hasMoved;
}

GLvoid PlayerShip::receiveHp(GLint hp) {
    this->hp += hp;

    if (this->hp > PlayerShip::maxHp)
        this->hp = PlayerShip::maxHp;
}

GLvoid PlayerShip::takeDamage(GLint dmg) {
    this->hp -= dmg;
}

GLboolean PlayerShip::isAlive() {
    this->hp > 0;
}

GLfloat* PlayerShip::getPosition() {
    return this->position;
}