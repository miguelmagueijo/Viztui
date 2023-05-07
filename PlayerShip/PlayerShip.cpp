//
// Created by migue on 30/04/2023.
//

#include "PlayerShip.h"

// Size ratio is 40:30 (4:3)
const GLfloat playerShipSize[2] = { 30.0f, 22.5f };
// Better use more memory than doing the division all the time it needs it
const GLfloat playerShipHalfSize[2] = { playerShipSize[0] / 2, playerShipSize[1] / 2 };

PlayerShip::PlayerShip() {
    this->speed = 1.5f;
}

PlayerShip::PlayerShip(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = 1.5f;
}

GLvoid PlayerShip::body(GLvoid) {
    glColor3f(0.77f, 0.61f, 0.19f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] / 4.0f, playerShipSize[1]);
        glVertex2f(playerShipHalfSize[0], 0);
    } glEnd();
}

GLvoid PlayerShip::cockpit(GLvoid) {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] * 0.1f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] * 0.3f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] / 10.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::leftWing(GLvoid) {
    glColor3f(0.0, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(playerShipHalfSize[0], 0.0f);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::rightWing(GLvoid) {
    glColor3f(0.0, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::cannon(GLvoid) {
    glColor3f(0.77f, 0.61f, 0.19f);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] * 0.1f / 4.0f, playerShipSize[1] / 10.0f);
        glVertex2f(playerShipSize[0] * 0.3f / 4.0f, playerShipSize[1] / 10.0f);
        glVertex2f(playerShipSize[0] / 10.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //glTranslatef(-this->position[0], -this->position[1], 0);
    //glRotatef(this->currentAngle, 0, 0, 1);
    //glTranslatef(this->position[0], this->position[1], 0);

    // Translation for body component / center of ship
    glTranslatef(this->position[0] - playerShipHalfSize[0], this->position[1] - playerShipHalfSize[1], 0);
    glPushMatrix();

    // Draw left wing
    this->leftWing();

    // Pop current matrix and create new one
    glPopMatrix();
    glPushMatrix();

    // Right wing translation and draw

    glTranslatef(playerShipHalfSize[0], 0, 0);
    this->rightWing();

    glPopMatrix();
    glPushMatrix();

    // Body draw, it's here because of wings overlapping if they are drawn after body
    glTranslatef(playerShipSize[0] / 4, 0, 0);

    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(playerShipSize[0] * 9 / 20, playerShipSize[1] * 11 / 30, 0.0f);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    // Left cannon draw
    glTranslatef(playerShipSize[0] * 9 / 40, playerShipHalfSize[1], 0.0f);
    this->cannon();

    glPopMatrix();
    glPushMatrix();

    // Right cannon draw
    glTranslatef(playerShipSize[0] * 27 / 40, playerShipHalfSize[1], 0.0f);
    this->cannon();

    glPopMatrix();
    glPopMatrix();
}

GLboolean PlayerShip::move(MOVE_DIRS dir) {
    GLboolean hasMoved = false;

    switch(dir) {
        case MOVE_DIRS::UP:
            if (this->position[1] + playerShipHalfSize[1] + this->speed < worldBorders[3]) {
                this->position[1] += this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::DOWN:
            if (this->position[1] - playerShipHalfSize[1] - this->speed > worldBorders[2]) {
                this->position[1] -= this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::LEFT:
            if (this->position[0] - playerShipHalfSize[0] - this->speed > worldBorders[0]) {
                this->position[0] -= this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::RIGHT:
            if (this->position[0] + playerShipHalfSize[0] + this->speed < worldBorders[1]) {
                this->position[0] += this->speed;
                hasMoved = true;
            }
            break;
    }

    std::cout << this->position[1] << std::endl;

    return hasMoved;
}

GLvoid PlayerShip::receiveHp(GLint hp) {
    this->hp += hp;

    if (this->hp > PlayerShip::maxHp)
        this->hp = PlayerShip::maxHp;
}

GLvoid PlayerShip::takeDamage(GLint dmg) {
    this->hp -= dmg;
}

GLboolean PlayerShip::isAlive() {
    this->hp > 0;
}

GLfloat* PlayerShip::getPosition() {
    return this->position;
}

GLvoid PlayerShip::rotate(GLboolean isCW) {
    if (isCW)
        this->currentAngle += 90;
    else
        this->currentAngle -= 90;

    if (abs(this->currentAngle) >= 360) {
        this->currentAngle = 0;
    }

    std::cout << this->currentAngle << std::endl;
}