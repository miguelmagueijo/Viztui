//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "Fighter.h"

// Size ratio = 20:10 (2:1)
GLfloat fighterSize[2] = { 20, 10 };

Fighter::Fighter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
}

Fighter::Fighter(GLfloat x, GLfloat y, GLfloat speed) : Fighter(x, y, speed, 30) {}

Fighter::Fighter(GLfloat x, GLfloat y) : Fighter(x, y, 2, 30) {}

Fighter::Fighter(GLvoid) : Fighter(0, 0, 2, 30) {}

GLvoid Fighter::body(GLvoid) {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, fighterSize[1] * 4 / 5);
        glVertex2f(fighterSize[0] * 2 / 5, fighterSize[1] * 4 / 5);
        glVertex2f(fighterSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid Fighter::cockpit(GLvoid) {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, fighterSize[1] * 2 / 5);
        glVertex2f(fighterSize[0] / 10, fighterSize[1] * 2 / 5);
        glVertex2f(fighterSize[0] / 10, 0);
    } glEnd();
}

GLvoid Fighter::cannon(GLvoid) {
    glColor3f(0.00f, 0.56f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, fighterSize[1] / 5);
        glVertex2f(fighterSize[0] / 10, fighterSize[1] / 5);
        glVertex2f(fighterSize[0] / 10, 0);
    } glEnd();
}

GLvoid Fighter::leftWing(GLvoid) {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, fighterSize[1]);
        glVertex2f(fighterSize[0] * 7 / 10, fighterSize[1]);
    } glEnd();
}

GLvoid Fighter::rightWing(GLvoid) {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(fighterSize[0] * 7 / 10, 0);
        glVertex2f(0, fighterSize[1]);
        glVertex2f(fighterSize[0] * 7 / 10, fighterSize[1]);
    } glEnd();
}

GLvoid Fighter::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - fighterSize[0] / 2, this->position[1] - fighterSize[1] / 2, 0);

    this->leftWing();

    glPushMatrix();

    glTranslatef(fighterSize[0] * 3 / 10, 0, 0);
    this->rightWing();

    glTranslatef(0, fighterSize[1] / 5, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(fighterSize[0] * 9 / 20, 0, 0);
    this->cannon();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(fighterSize[0] * 9 / 20, fighterSize[1] * 3 / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPopMatrix();
}