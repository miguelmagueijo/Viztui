//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "SoldierTransporter.h"

SoldierTransporter::SoldierTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) : Enemy(x, y, speed, hp) {}

GLvoid SoldierTransporter::body() {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1]);
        glVertex2f(enemySize[0] * 3 / 5, enemySize[1]);
        glVertex2f(enemySize[0] * 3 / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::cockpit() {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1] / 5);
        glVertex2f(enemySize[0] / 5, enemySize[1] / 5);
        glVertex2f(enemySize[0] / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::rocket() {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1] * 2 / 5);
        glVertex2f(enemySize[0] / 5, enemySize[1] * 2 / 5);
        glVertex2f(enemySize[0] / 5, 0);
    } glEnd();
}

GLvoid SoldierTransporter::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - enemySize[0] / 2, this->position[1] - enemySize[1] / 2, 0);

    glPushMatrix();

    glTranslatef(enemySize[0] / 5, 0, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(enemySize[0] * 2 / 5, enemySize[1] / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    // Lower Left Rocket
    this->rocket();

    // Upper Left Rocket
    glTranslatef(0, enemySize[1] * 3 / 5, 0);
    this->rocket();

    glPopMatrix();
    glPushMatrix();

    // Lower Right Rocket
    glTranslatef(enemySize[0] * 4 / 5, 0.0f, 0.0f);
    this->rocket();

    // Upper Right Rocket
    glTranslatef(0.0f, enemySize[1] * 3 / 5, 0.0f);
    this->rocket();

    glPopMatrix();
    glPopMatrix();
}