//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "SoldierTransporter.h"

// Size ratio = 20:10 (2:1)
GLfloat soldierTransporterSize[2] = { 20.0f, 10.0f };

SoldierTransporter::SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
}

SoldierTransporter::SoldierTransporter(GLvoid) : SoldierTransporter(0, 0, 2, 30) {}

SoldierTransporter::SoldierTransporter(GLfloat x, GLfloat y) : SoldierTransporter(x, y, 2, 30) {}

SoldierTransporter::SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed) : SoldierTransporter(x, y, speed, 30) {}

GLvoid SoldierTransporter::body(GLvoid) {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, soldierTransporterSize[1]);
        glVertex2f(soldierTransporterSize[0] * 3 / 5, soldierTransporterSize[1]);
        glVertex2f(soldierTransporterSize[0] * 3 / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::cockpit(GLvoid) {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, soldierTransporterSize[1] / 5);
        glVertex2f(soldierTransporterSize[0] / 5, soldierTransporterSize[1] / 5);
        glVertex2f(soldierTransporterSize[0] / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::rocket(GLvoid) {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, soldierTransporterSize[1] * 2 / 5);
        glVertex2f(soldierTransporterSize[0] / 5, soldierTransporterSize[1] * 2 / 5);
        glVertex2f(soldierTransporterSize[0] / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - soldierTransporterSize[0] / 2, this->position[1] - soldierTransporterSize[0] / 2, 0);

    glPushMatrix();

    glTranslatef(soldierTransporterSize[0] / 5, 0, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(soldierTransporterSize[0] * 2 / 5, soldierTransporterSize[1] / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    // Lower Left Rocket
    this->rocket();

    // Upper Left Rocket
    glTranslatef(0, soldierTransporterSize[1] * 3 / 5, 0);
    this->rocket();

    glPopMatrix();
    glPushMatrix();

    // Lower Right Rocket
    glTranslatef(soldierTransporterSize[0] * 4 / 5, 0.0f, 0.0f);
    this->rocket();

    // Upper Right Rocket
    glTranslatef(0.0f, soldierTransporterSize[1] * 3 / 5, 0.0f);
    this->rocket();

    glPopMatrix();
    glPopMatrix();
}

GLvoid SoldierTransporter::move(MOVE_DIRECTIONS dir) {
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
}

GLfloat* SoldierTransporter::getPosition(GLvoid) {
    return this->position;
}

GLvoid SoldierTransporter::takeDamage(GLfloat dmg) {
    this->hp -= dmg;
}

GLboolean SoldierTransporter::isAlive(GLvoid) {
    return this->hp > 0;
}