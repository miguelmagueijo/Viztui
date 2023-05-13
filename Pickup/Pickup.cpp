//
// Created by Miguel Magueijo on 09/05/2023.
//

#include "Pickup.h"

const GLfloat pickupSize[2] = { 10, 7 };
const GLfloat pickupHalfSize[2] = { pickupSize[0] / 2, pickupSize[1] / 2 };

Pickup::Pickup(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) {
    this->position[0] = x;
    this->position[1] = y;
    this->dir = dir;
    this->speed = speed;
}

// By default pos is x:0 y:0, speed of 1 and moves down
Pickup::Pickup() : Pickup(0, 0, MOVE_DIRS::DOWN, 1) {}

GLvoid Pickup::background() {
    glColor3f(0.86f, 0.86f, 0.86f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1]);
        glVertex2f(pickupSize[0], pickupSize[1]);
        glVertex2f(pickupSize[0], 0);
    } glEnd();
}

GLvoid Pickup::setPosition(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
}

GLvoid Pickup::setDirection(MOVE_DIRS d) {
    this->dir = d;
}

GLvoid Pickup::setSpeed(GLfloat s) {
    if (s <= 0) throw std::invalid_argument("Pickup speed must be greater than 0");
}

GLfloat* Pickup::getPosition() {
    return this->position;
}

GLvoid Pickup::move() {
    switch(this->dir) {
        case MOVE_DIRS::DOWN:
            this->position[1] -= this->speed;
            break;
        case MOVE_DIRS::UP:
            this->position[1] += this->speed;
            break;
        case MOVE_DIRS::LEFT:
            this->position[0] -= this->speed;
            break;
        case MOVE_DIRS::RIGHT:
            this->position[0] += this->speed;
            break;
    }
}