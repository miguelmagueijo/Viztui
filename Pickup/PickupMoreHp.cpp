//
// Created by Miguel Magueijo on 10/05/2023.
//

#include "PickupMoreHp.h"

GLfloat PickupMoreHp::size[2] = { 8, 5 };
GLfloat PickupMoreHp::halfSize[2] = { PickupMoreHp::size[0] / 2, PickupMoreHp::size[1] / 2 };

PickupMoreHp::PickupMoreHp(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) : Pickup(x, y, dir, speed) {
    this->hpGain = 1;
}

GLvoid PickupMoreHp::setHpGain(GLshort h) {
    if (h < 0) throw std::invalid_argument("Bad hp gain value, must be >=0");

    this->hpGain = h;
}

GLvoid PickupMoreHp::leftArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupMoreHp::size[1] * 3 / 5);
        glVertex2f(PickupMoreHp::halfSize[0], 0);
    } glEnd();
}

GLvoid PickupMoreHp::rightArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(PickupMoreHp::halfSize[0], PickupMoreHp::size[1] * 3 / 5);
        glVertex2f(PickupMoreHp::halfSize[0], 0);
    } glEnd();
}

GLvoid PickupMoreHp::bottomTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(PickupMoreHp::size[0] / 4, 0);
        glVertex2f(0, PickupMoreHp::size[1] * 2 / 5);
        glVertex2f(PickupMoreHp::halfSize[0], PickupMoreHp::size[1] * 2 / 5);
    } glEnd();
}

GLvoid PickupMoreHp::rectVertical() {
    glColor3f(1, 0, 0);

    glBegin(GL_QUADS); {
        glVertex2f( 0, 0);
        glVertex2f( 0, PickupMoreHp::size[1] * 3 / 5);
        glVertex2f( PickupMoreHp::size[0] / 8, PickupMoreHp::size[1] * 3 / 5);
        glVertex2f( PickupMoreHp::size[0] / 8, 0);

    } glEnd();
}

GLvoid PickupMoreHp::rectHorizontal() {
    glColor3f(1, 0, 0);

    glBegin(GL_QUADS); {
        glVertex2f( 0, 0);
        glVertex2f( 0, PickupMoreHp::size[1] / 5);
        glVertex2f( PickupMoreHp::size[0] * 3 / 8, PickupMoreHp::size[1] / 5);
        glVertex2f( PickupMoreHp::size[0] * 3 / 8, 0);

    } glEnd();
}

GLvoid PickupMoreHp::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - PickupMoreHp::halfSize[0], this->position[1] - PickupMoreHp::halfSize[1], 0);

    this->bottomTriangle();

    glPushMatrix();

    glTranslatef(0, PickupMoreHp::size[1] * 2 / 5, 0);
    this->leftArcTriangle();
    this->rightArcTriangle();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(PickupMoreHp::size[0] * 5 / 8, PickupMoreHp::size[1] * 2 / 5, 0);
    this->rectHorizontal();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(PickupMoreHp::size[0] * 3 / 4, PickupMoreHp::size[1] / 5, 0);
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