//
// Created by Miguel Magueijo on 07/05/2023.
//

#include "Enemy.h"

const GLfloat Enemy::PRIMARY_COLOR[3] = { 0.87f, 0.44f, 0.44f };
const GLfloat Enemy::SPECIAL_PRIMARY_COLOR[3] = { 0.87f, 0.78f, 0.44f };
const GLfloat Enemy::SECONDARY_COLOR[3] = { 0.29f, 0.31f, 0.76f };
const GLfloat Enemy::COCKPIT_COLOR[3] = { 0.34f, 0.60f, 1.00f };

Enemy::Enemy(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
    this->hasPickup = false;
}

GLvoid Enemy::setPickup(Pickup *p) {
    this->pickup = p;
    this->hasPickup = true;
}

GLboolean Enemy::dropsPickup() {
    return this->hasPickup;
}

Pickup* Enemy::getPickup() {
    Pickup* newPickup = this->pickup->clone();

    newPickup->setPosition(this->position[0], this->position[1]);

    return newPickup;
}

GLfloat* Enemy::getPosition() {
    return this->position;
}

GLvoid Enemy::takeDamage(GLfloat dmg) {
    this->hp -= dmg;
}

GLboolean Enemy::isAlive() {
    return this->hp > 0;
}

GLvoid Enemy::move(MOVE_DIRS dir) {
    switch(dir) {
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


