//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(GLfloat x, GLfloat y, MOVE_DIRS dir) : Bullet(x, y, dir) {}

EnemyBullet::EnemyBullet() : Bullet() {}

GLboolean EnemyBullet::damagesPlayer() {
    return true;
}

GLvoid EnemyBullet::body() {
    glColor3f(0.00f, 0.56f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid EnemyBullet::head() {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid EnemyBullet::draw() {
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

EnemyBullet* EnemyBullet::clone() {
    return new EnemyBullet(*this);
}