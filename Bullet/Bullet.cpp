//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "Bullet.h"

// Size ratio is 3:5
const GLfloat bulletSize[2] = { 3, 5 };
const GLfloat bulletHalfSize[2] = { bulletSize[0] / 2, bulletSize[1] / 2 };

Bullet::Bullet(GLfloat x, GLfloat y, MOVE_DIRS dir, GLboolean firedByPlayer) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = 1;
    this->damage = 1;
    this->firedByPlayer = firedByPlayer;
    this->setDirection(dir); // also sets angle
}

Bullet::Bullet(GLboolean firedByPlayer) : Bullet(0, 0, MOVE_DIRS::UP, firedByPlayer) {}

GLvoid Bullet::setPosition(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
}

GLvoid Bullet::setSpeed(GLfloat s) {
    if (s < 0) throw std::invalid_argument("Bad bullet speed, needs to be >=0.");

    this->speed = s;
}

GLvoid Bullet::setDamage(GLfloat d) {
    if (d < 0) throw std::invalid_argument("Bad bullet damage, needs to be >=0.");

    this->damage = d;
}

GLvoid Bullet::setDirection(MOVE_DIRS d) {
    this->dir = d;

    switch (this->dir) {
        case MOVE_DIRS::UP:
            this->angle = 0;
            break;
        case MOVE_DIRS::DOWN:
            this->angle = 180;
            break;
        case MOVE_DIRS::LEFT:
            this->angle = 90;
            break;
        case MOVE_DIRS::RIGHT:
            this->angle = -90;
            break;
    }
}

GLfloat* Bullet::getPosition() {
    return this->position;
}

GLfloat Bullet::getDamage() {
    return this->damage;
}

GLboolean Bullet::damagesPlayer()  {
    return !this->firedByPlayer;
}

GLvoid Bullet::move() {
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

GLvoid Bullet::body() {
    if (this->firedByPlayer)
        glColor3f(0.42f, 0.50f, 0.39f);
    else
        glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 3 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid Bullet::head() {
    if (this->firedByPlayer)
        glColor3f(0.78f, 0.61f, 0.19f);
    else
        glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], bulletSize[1] * 2 / 5);
        glVertex2f(bulletSize[0], 0.0f);
    } glEnd();
}

GLvoid Bullet::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - bulletHalfSize[0], this->position[1] - bulletHalfSize[1], 0.0f);

    glTranslatef(bulletHalfSize[0], bulletHalfSize[1], 0);
    glRotatef(this->angle, 0, 0, 1);
    glTranslatef(-bulletHalfSize[0], -bulletHalfSize[1], 0);

    this->body();

    glPushMatrix();

    glTranslatef(0.0f, bulletSize[1] * 3 / 5, 0.0f);
    this->head();

    glPopMatrix();
    glPopMatrix();
}

Bullet* Bullet::clone() {
    return new Bullet(*this);
}