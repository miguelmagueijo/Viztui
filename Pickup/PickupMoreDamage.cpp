//
// Created by Miguel Magueijo on 10/05/2023.
//

#include "PickupMoreDamage.h"

GLfloat PickupMoreDamage::size[2] = { 8, 5 };
GLfloat PickupMoreDamage::halfSize[2] = { PickupMoreDamage::size[0] / 2, PickupMoreDamage::size[1] / 2 };

PickupMoreDamage::PickupMoreDamage(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) : Pickup(x, y, dir, speed) {
    this->dmgGain = 5;
}

GLvoid PickupMoreDamage::triangle() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(PickupMoreDamage::size[0] * 5 / 16, PickupMoreDamage::size[1]);
        glVertex2f(PickupMoreDamage::size[0] * 5 / 8, 0);
    } glEnd();
}

GLvoid PickupMoreDamage::bulletBody() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupMoreDamage::size[1] * 3 / 5);
        glVertex2f(PickupMoreDamage::size[0] / 4, PickupMoreDamage::size[1] * 3 / 5);
        glVertex2f(PickupMoreDamage::size[0] / 4, 0);
    } glEnd();
}

GLvoid PickupMoreDamage::bulletHead() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupMoreDamage::size[1] * 2 / 5);
        glVertex2f(PickupMoreDamage::size[0] / 4, PickupMoreDamage::size[1] * 2 / 5);
        glVertex2f(PickupMoreDamage::size[0] / 4, 0);
    } glEnd();
}

GLvoid PickupMoreDamage::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - PickupMoreDamage::halfSize[0], this->position[1] - PickupMoreDamage::halfSize[1], 0);

    this->bulletBody();

    glPushMatrix();

    glTranslatef(0, PickupMoreDamage::size[1] * 3 / 5, 0);
    this->bulletHead();


    glPopMatrix();
    glPushMatrix();

    glTranslatef(PickupMoreDamage::size[0] * 3 / 8, 0, 0);
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