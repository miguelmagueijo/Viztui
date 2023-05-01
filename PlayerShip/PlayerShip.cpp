//
// Created by migue on 30/04/2023.
//

#include "PlayerShip.h"

// Ratio of 4:3
GLfloat playerShipSize[2] = { 40.0f, 30.0f };

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
    glColor3f(0.0f, 0.0f, 1.0f);

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