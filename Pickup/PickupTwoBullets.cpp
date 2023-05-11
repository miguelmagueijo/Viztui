//
// Created by Miguel Magueijo on 11/05/2023.
//

#include "PickupTwoBullets.h"

GLfloat PickupTwoBullets::size[2] = { 8, 6 };
GLfloat PickupTwoBullets::halfSize[2] = { PickupTwoBullets::size[0] / 2, PickupTwoBullets::size[1] / 2 };

PickupTwoBullets::PickupTwoBullets(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) : Pickup(x, y, dir, speed) {}

GLvoid PickupTwoBullets::bulletBody() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupTwoBullets::size[1] * 5 / 6);
        glVertex2f(PickupTwoBullets::size[0] / 4, PickupTwoBullets::size[1] * 5 / 6);
        glVertex2f(PickupTwoBullets::size[0] / 4, 0);
    } glEnd();
}

GLvoid PickupTwoBullets::bulletHead() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupTwoBullets::size[1] / 3);
        glVertex2f(PickupTwoBullets::size[0] / 4, PickupTwoBullets::size[1] / 3);
        glVertex2f(PickupTwoBullets::size[0] / 4, 0);
    } glEnd();
}

GLvoid PickupTwoBullets::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - PickupTwoBullets::halfSize[0], this->position[1] - PickupTwoBullets::halfSize[1], 0);

    this->bulletBody();

    glPushMatrix();

    glTranslatef(0, PickupTwoBullets::halfSize[1], 0);
    this->bulletHead();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(PickupTwoBullets::size[0] * 3 / 8, 0, 0);
    this->bulletBody();
    glTranslatef(0, PickupTwoBullets::size[1] * 2 / 3, 0);
    this->bulletHead();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(PickupTwoBullets::size[0] * 3 / 4, 0, 0);
    this->bulletBody();
    glTranslatef(0, PickupTwoBullets::halfSize[1], 0);
    this->bulletHead();

    glPopMatrix();
    glPopMatrix();
}

GLvoid PickupTwoBullets::playerEffect(PlayerShip* playerShip) {
    playerShip->setFireExtra(true);
}

Pickup* PickupTwoBullets::clone() {
    return new PickupTwoBullets(*this);
}