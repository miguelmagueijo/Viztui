//
// Created by migue on 30/04/2023.
//

#include "PlayerShip.h"

// Size ratio is 40:30 (4:3)
const GLfloat playerShipSize[2] = { 30.0f, 22.5f };
// Better use more memory than doing the division all the time it needs it
const GLfloat playerShipHalfSize[2] = { playerShipSize[0] / 2, playerShipSize[1] / 2 };

const GLfloat PlayerShip::PRIMARY_COLOR[3] = { 0.78f, 0.61f, 0.19f };
const GLfloat PlayerShip::SECONDARY_COLOR[3] = { 0.42f, 0.50f, 0.39f };
const GLfloat PlayerShip::COCKPIT_COLOR[3] = { 0.34f, 0.60f, 1.00f };

PlayerShip::PlayerShip(GLfloat x, GLfloat y, GLfloat speed, GLshort hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
    this->bulletDmg = 5;
    this->bullet = new Bullet(true);
    this->bullet->setSpeed(3);
    this->bullet->setDamage(5);
    this->canFireExtra = false;
    this->currentAngle = 0;
}

GLvoid PlayerShip::setFireExtra(GLboolean fExtra) {
    this->canFireExtra = fExtra;
}

GLfloat* PlayerShip::getPosition() {
    return this->position;
}

GLshort PlayerShip::getHp() {
    return this->hp;
}

GLshort PlayerShip::getMaxHp() {
    return PlayerShip::maxHp;
}

GLvoid PlayerShip::body() {
    glColor3f(PlayerShip::PRIMARY_COLOR[0], PlayerShip::PRIMARY_COLOR[1], PlayerShip::PRIMARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] / 4.0f, playerShipSize[1]);
        glVertex2f(playerShipHalfSize[0], 0);
    } glEnd();
}

GLvoid PlayerShip::cockpit() {
    glColor3f(PlayerShip::COCKPIT_COLOR[0], PlayerShip::COCKPIT_COLOR[1], PlayerShip::COCKPIT_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(playerShipSize[0] * 0.1f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] * 0.3f / 4.0f, playerShipSize[1] / 5.0f);
        glVertex2f(playerShipSize[0] / 10.0f, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::leftWing() {
    glColor3f(PlayerShip::SECONDARY_COLOR[0], PlayerShip::SECONDARY_COLOR[1], PlayerShip::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(playerShipHalfSize[0], 0.0f);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::rightWing(GLvoid) {
    glColor3f(PlayerShip::SECONDARY_COLOR[0], PlayerShip::SECONDARY_COLOR[1], PlayerShip::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::cannon(GLvoid) {
    glColor3f(PlayerShip::PRIMARY_COLOR[0], PlayerShip::PRIMARY_COLOR[1], PlayerShip::PRIMARY_COLOR[2]);

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

    // Translation to center ship in position
    glTranslatef(this->position[0] - playerShipHalfSize[0], this->position[1] - playerShipHalfSize[1], 0);

    // Rotation
    glTranslatef(playerShipHalfSize[0], playerShipHalfSize[1], 0);
    glRotatef(this->currentAngle, 0, 0, 1);
    glTranslatef(-playerShipHalfSize[0], -playerShipHalfSize[1], 0);

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

    return hasMoved;
}

GLvoid PlayerShip::receiveHp(GLshort hp) {
    this->hp += hp;

    if (this->hp > PlayerShip::maxHp)
        this->hp = PlayerShip::maxHp;
}

GLvoid PlayerShip::increaseBulletDmg(GLfloat dmg) {
    if (dmg < 0) throw std::invalid_argument("Bullet damage increase needs to be >=0");

    this->bullet->setDamage(this->bullet->getDamage() + dmg);
}

GLvoid PlayerShip::takeDamage(GLshort dmg) {
    if (dmg < 0) throw std::invalid_argument("Player can only take damage >= 0");

    this->hp -= dmg;
}

GLboolean PlayerShip::isAlive() {
    return this->hp > 0;
}

GLvoid PlayerShip::rotate(MOVE_DIRS rDir) {
    switch (rDir) {
        case MOVE_DIRS::RIGHT:
            this->currentAngle -= 90;
            break;
        case MOVE_DIRS::LEFT:
            this->currentAngle += 90;
            break;
        default:
            return;
    }

    if (abs(this->currentAngle) >= 360) {
        this->currentAngle = 0;
    }
}

std::vector<Bullet*> PlayerShip::fireBullet() {
    std::vector<Bullet*> bullets;

    Bullet* newBullet = this->bullet->clone();

    switch (this->currentAngle) {
        case 0:
            newBullet->setPosition(this->position[0], this->position[1] + playerShipHalfSize[1] + 2);
            newBullet->setDirection(MOVE_DIRS::UP);
            break;
        case -90:
        case 270:
            newBullet->setPosition(this->position[0] + playerShipHalfSize[0] + 2, this->position[1]);
            newBullet->setDirection(MOVE_DIRS::RIGHT);
            break;
        case -180:
        case 180:
            newBullet->setPosition(this->position[0], this->position[1] - playerShipHalfSize[1] - 2);
            newBullet->setDirection(MOVE_DIRS::DOWN);
            break;
        case -270:
        case 90:
            newBullet->setPosition(this->position[0] - playerShipHalfSize[1] - 2, this->position[1]);
            newBullet->setDirection(MOVE_DIRS::LEFT);
            break;
    }

    bullets.push_back(newBullet);

    if (this->canFireExtra) {
        Bullet* leftBullet = this->bullet->clone();
        Bullet* rightBullet = this->bullet->clone();

        leftBullet->setDamage(this->bulletDmg / 2);
        rightBullet->setDamage(this->bulletDmg / 2);

        switch (this->currentAngle) {
            case 0:
                leftBullet->setPosition(this->position[0] - playerShipSize[0] * 9 / 40, this->position[1] + playerShipSize[1] * 2 / 15);
                rightBullet->setPosition(this->position[0] + playerShipSize[0] * 9 / 40, this->position[1] + playerShipSize[1] * 2 / 15);
                leftBullet->setDirection(MOVE_DIRS::UP);
                rightBullet->setDirection(MOVE_DIRS::UP);
                break;
            case -90:
            case 270:
                leftBullet->setPosition(this->position[0] + playerShipSize[1] * 2 / 15, this->position[1] + playerShipSize[0] * 9 / 40);
                rightBullet->setPosition(this->position[0] + playerShipSize[1] * 2 / 15, this->position[1] - playerShipSize[0] * 9 / 40);
                leftBullet->setDirection(MOVE_DIRS::RIGHT);
                rightBullet->setDirection(MOVE_DIRS::RIGHT);
                break;
            case -180:
            case 180:
                leftBullet->setPosition(this->position[0] + playerShipSize[0] * 9 / 40, this->position[1] - playerShipSize[1] * 2 / 15);
                rightBullet->setPosition(this->position[0] - playerShipSize[0] * 9 / 40, this->position[1] - playerShipSize[1] * 2 / 15);
                leftBullet->setDirection(MOVE_DIRS::DOWN);
                rightBullet->setDirection(MOVE_DIRS::DOWN);
                break;
            case -270:
            case 90:
                leftBullet->setPosition(this->position[0] - playerShipSize[1] * 2 / 15, this->position[1] - playerShipSize[0] * 9 / 40);
                rightBullet->setPosition(this->position[0] - playerShipSize[1] * 2 / 15, this->position[1] + playerShipSize[0] * 9 / 40);
                leftBullet->setDirection(MOVE_DIRS::LEFT);
                rightBullet->setDirection(MOVE_DIRS::LEFT);
                break;
        }

        bullets.insert(bullets.end(), {leftBullet, rightBullet});
    }

    return bullets;
}