//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "Fighter.h"

Fighter::Fighter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) : Enemy(x, y, speed, hp) {};

GLvoid Fighter::body() {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1] * 4 / 5);
        glVertex2f(enemySize[0] * 2 / 5, enemySize[1] * 4 / 5);
        glVertex2f(enemySize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid Fighter::cockpit() {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1] * 2 / 5);
        glVertex2f(enemySize[0] / 10, enemySize[1] * 2 / 5);
        glVertex2f(enemySize[0] / 10, 0);
    } glEnd();
}

GLvoid Fighter::cannon() {
    glColor3f(0.00f, 0.56f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1] / 5);
        glVertex2f(enemySize[0] / 10, enemySize[1] / 5);
        glVertex2f(enemySize[0] / 10, 0);
    } glEnd();
}

GLvoid Fighter::leftWing() {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, enemySize[1]);
        glVertex2f(enemySize[0] * 7 / 10, enemySize[1]);
    } glEnd();
}

GLvoid Fighter::rightWing() {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(enemySize[0] * 7 / 10, 0);
        glVertex2f(0, enemySize[1]);
        glVertex2f(enemySize[0] * 7 / 10, enemySize[1]);
    } glEnd();
}

GLvoid Fighter::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - enemySize[0] / 2, this->position[1] - enemySize[1] / 2, 0);

    this->leftWing();

    glPushMatrix();

    glTranslatef(enemySize[0] * 3 / 10, 0, 0);
    this->rightWing();

    glTranslatef(0, enemySize[1] / 5, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(enemySize[0] * 9 / 20, 0, 0);
    this->cannon();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(enemySize[0] * 9 / 20, enemySize[1] * 3 / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPopMatrix();
}