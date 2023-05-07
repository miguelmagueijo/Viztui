//
// Created by Miguel Magueijo on 07/05/2023.
//

#include "Enemy.h"



Enemy::Enemy(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
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


