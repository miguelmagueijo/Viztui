//
// Created by Miguel Magueijo on 10/05/2023.
//

#include "PickupMoreDamage.h"

// Gives player bullets more damage
PickupMoreDamage::PickupMoreDamage(GLfloat dmgGain) : Pickup() {
    this->setDamageGain(dmgGain);
}

GLvoid PickupMoreDamage::setDamageGain(GLfloat dg) {
    if (dg <= 0) throw std::invalid_argument("Pickup (MoreDamage) damage gain must be greater than 0");
}

GLvoid PickupMoreDamage::triangle() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(pickupHalfSize[0] / 2, pickupSize[1] * 5 / 7);
        glVertex2f(pickupHalfSize[0], 0);
    } glEnd();
}

GLvoid PickupMoreDamage::bulletBody() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] / 5, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] / 5, 0);
    } glEnd();
}

GLvoid PickupMoreDamage::bulletHead() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 2 / 7);
        glVertex2f(pickupSize[0] / 5, pickupSize[1] * 2 / 7);
        glVertex2f(pickupSize[0] / 5, 0);
    } glEnd();
}

GLvoid PickupMoreDamage::draw() {
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
    this->triangle();

    glPopMatrix();
    glPopMatrix();
}

GLvoid PickupMoreDamage::playerEffect(PlayerShip* playerShip) {
    playerShip->increaseBulletDmg(this->dmgGain);
}

PickupMoreDamage* PickupMoreDamage::clone() {
    return new PickupMoreDamage(*this);
}