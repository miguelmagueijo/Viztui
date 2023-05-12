//
// Created by Miguel Magueijo on 09/05/2023.
//

#include "Pickup.h"

Pickup::Pickup(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) {
    this->position[0] = x;
    this->position[1] = y;
    this->dir = dir;
    this->speed = speed;
}

Pickup::Pickup(MOVE_DIRS dir, GLfloat speed) : Pickup(0, 0, dir, speed) {}

GLvoid Pickup::setPosition(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
}

GLfloat* Pickup::getPosition() {
    return this->position;
}

GLvoid Pickup::move() {
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