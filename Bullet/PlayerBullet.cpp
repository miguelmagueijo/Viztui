//
// Created by Miguel Magueijo on 02/05/2023.
//

#include "PlayerBullet.h"

GLfloat playerBulletSize[2] = { 2, 5};

PlayerBullet::PlayerBullet(GLfloat x, GLfloat y, GLfloat speed, GLfloat dmg, MOVE_DIRS dir) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->damage = dmg;
    this->dir = dir;
}

PlayerBullet::PlayerBullet() : PlayerBullet(0, 0, 2, 5, MOVE_DIRS::UP) { }

GLvoid PlayerBullet::setPosition(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
}

GLfloat* PlayerBullet::getPosition() {
    return this->position;
}

GLfloat PlayerBullet::getDamage() {
    return this->damage;
}

GLvoid PlayerBullet::body() {
    glColor3f(0.42f, 0.50f, 0.39f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 3.0f);
        glVertex2f(2.0f, 3.0f);
        glVertex2f(2.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::head() {
    glColor3f(0.78f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 2.0f);
        glVertex2f(2.0f, 2.0f);
        glVertex2f(2.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerBullet::draw() {
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

GLvoid PlayerBullet::move() {
    switch(this->dir) {
        case MOVE_DIRS::UP:
            this->position[1] += this->speed;
            break;
        case MOVE_DIRS::DOWN:
            this->position[1] -= this->speed;
            break;
        case MOVE_DIRS::LEFT:
            this->position[0] -= this->speed;
            break;
        case MOVE_DIRS::RIGHT:
            this->position[0] += this->speed;
            break;
    }
}

PlayerBullet* PlayerBullet::clone() {
    return new PlayerBullet(*this);
}