//
// Created by Miguel Magueijo on 11/05/2023.
//

#include "PickupTwoBullets.h"

PickupTwoBullets::PickupTwoBullets() : Pickup() {}

GLvoid PickupTwoBullets::bulletBody() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] / 5, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] / 5, 0);
    } glEnd();
}

GLvoid PickupTwoBullets::bulletHead() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 2 / 7);
        glVertex2f(pickupSize[0] / 5, pickupSize[1] * 2 / 7);
        glVertex2f(pickupSize[0] / 5, 0);
    } glEnd();
}

GLvoid PickupTwoBullets::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - pickupHalfSize[0], this->position[1] - pickupHalfSize[1], 0);

    this->background();

    glPushMatrix();

    glTranslatef(pickupSize[0] / 10, pickupSize[1] / 7, 0);
    this->bulletBody();

    glTranslatef(0, pickupSize[1] * 3 / 7, 0);
    this->bulletHead();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(pickupSize[0] * 2 / 5, pickupSize[1] / 7, 0);
    this->bulletBody();

    glTranslatef(0, pickupSize[1] * 3 / 7, 0);
    this->bulletHead();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(pickupSize[0] * 7 / 10, pickupSize[1] / 7, 0);
    this->bulletBody();

    glTranslatef(0, pickupSize[1] * 3 / 7, 0);
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