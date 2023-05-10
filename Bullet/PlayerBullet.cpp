//
// Created by Miguel Magueijo on 02/05/2023.
//

#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(GLfloat x, GLfloat y, MOVE_DIRS dir) : Bullet(x, y, dir) {}

PlayerBullet::PlayerBullet() : Bullet() {}

GLboolean PlayerBullet::damagesPlayer() {
    return false;
}

GLvoid PlayerBullet::body() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::head() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - 1.0f, this->position[1] - 2.5f, 0.0f);

    glTranslatef(bulletHalfSize[0], bulletHalfSize[1], 0);
    glRotatef(this->angle, 0, 0, 1);
    glTranslatef(-bulletHalfSize[0], -bulletHalfSize[1], 0);

    this->body();

    glPushMatrix();

    glTranslatef(0.0f, 3.0f, 0.0f);
    this->head();

    glPopMatrix();
    glPopMatrix();
}

PlayerBullet* PlayerBullet::clone() {
    return new PlayerBullet(*this);
}