//
// Created by Miguel Magueijo on 02/05/2023.
//

#include "PlayerBullet.h"

GLfloat playerBulletSize[2] = { 2, 5};

PlayerBullet::PlayerBullet() {
    this->position[0] = 0.0f;
    this->position[1] = 0.0f;
    this->speed = 2.0f;
    this->damage = 2.0f;
}

PlayerBullet::PlayerBullet(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = 2.0f;
    this->damage = 2.0f;
}

GLvoid PlayerBullet::body(GLvoid) {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 3.0f);
        glVertex2f(2.0f, 3.0f);
        glVertex2f(2.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::head(GLvoid) {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 2.0f);
        glVertex2f(2.0f, 2.0f);
        glVertex2f(2.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - 1.0f, this->position[1] - 2.5f, 0.0f);
    this->body();

    glPushMatrix();

    glTranslatef(0.0f, 3.0f, 0.0f);
    this->head();

    glPopMatrix();
    glPopMatrix();
}