//
// Created by Miguel Magueijo on 10/05/2023.
//

#include "PickupMoreHp.h"

PickupMoreHp::PickupMoreHp(GLint hpGain) : Pickup() {
    this->setHpGain(hpGain);
}

GLvoid PickupMoreHp::setHpGain(GLint h) {
    if (h <= 0) throw std::invalid_argument("Pickup (MoreHp) hp gain must be greater than 0");

    this->hpGain = h;
}

GLvoid PickupMoreHp::leftArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid PickupMoreHp::rightArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(pickupSize[0] * 2 / 5, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid PickupMoreHp::bottomTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(pickupSize[0] / 5, 0);
        glVertex2f(0, pickupSize[1] * 2 / 7);
        glVertex2f(pickupSize[0] * 2 / 5, pickupSize[1] * 2 / 7);
    } glEnd();
}

GLvoid PickupMoreHp::rectVertical() {
    glColor3f(1, 0, 0);

    glBegin(GL_QUADS); {
        glVertex2f( 0, 0);
        glVertex2f( 0, pickupSize[1] * 3 / 7);
        glVertex2f( pickupSize[0] / 10, pickupSize[1] * 3 / 7);
        glVertex2f( pickupSize[0] / 10, 0);

    } glEnd();
}

GLvoid PickupMoreHp::rectHorizontal() {
    glColor3f(1, 0, 0);

    glBegin(GL_QUADS); {
        glVertex2f( 0, 0);
        glVertex2f( 0, pickupSize[1] / 7);
        glVertex2f( pickupSize[0] * 3 / 10, pickupSize[1] / 7);
        glVertex2f( pickupSize[0] * 3 / 10, 0);

    } glEnd();
}

GLvoid PickupMoreHp::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - pickupHalfSize[0], this->position[1] - pickupHalfSize[1], 0);

    this->background();

    glPushMatrix();

    glTranslatef(pickupSize[0] / 10, pickupSize[1] / 7, 0);
    this->bottomTriangle();

    glTranslatef(0, pickupSize[1] * 2 / 7, 0);
    this->leftArcTriangle();
    this->rightArcTriangle();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(pickupSize[0] * 3 / 5, pickupSize[1] * 3 / 7, 0);
    this->rectHorizontal();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(pickupSize[0] * 7 / 10, pickupSize[1] * 2 / 7, 0);
    this->rectVertical();

    glPopMatrix();
    glPopMatrix();
}

GLvoid PickupMoreHp::playerEffect(PlayerShip* playerShip) {
    playerShip->receiveHp(this->hpGain);
}

PickupMoreHp* PickupMoreHp::clone() {
    return new PickupMoreHp(*this);
}