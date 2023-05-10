//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "Bullet.h"

Bullet::Bullet(GLfloat x, GLfloat y, GLboolean firedByPlayer, MOVE_DIRS dir) {
    this->position[0] = x;
    this->position[1] = y;
    this->firedByPlayer = firedByPlayer;
    setDirection(dir); // also sets angle
};

Bullet::Bullet() {}

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

GLboolean Bullet::isFiredByPlayer() {
    return this->firedByPlayer;
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