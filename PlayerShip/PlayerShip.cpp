//
// Created by migue on 30/04/2023.
//

#include "PlayerShip.h"

// Size ratio is 40:30 (4:3)
const GLfloat playerShipSize[2] = { 30.0f, 22.5f };
// Better use more memory than doing the division all the time it needs it
const GLfloat playerShipHalfSize[2] = { playerShipSize[0] / 2, playerShipSize[1] / 2 };

GLfloat playerHitbox[2] = { playerShipSize[0], playerShipSize[1] };
GLfloat playerHalfHitbox[2] = { playerShipHalfSize[0], playerShipHalfSize[1] };

const GLfloat PlayerShip::PRIMARY_COLOR[3] = { 0.78f, 0.61f, 0.19f };
const GLfloat PlayerShip::SECONDARY_COLOR[3] = { 0.42f, 0.50f, 0.39f };
const GLfloat PlayerShip::COCKPIT_COLOR[3] = { 0.34f, 0.60f, 1.00f };

const GLfloat PlayerShip::bulletSpace = 2;

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
        glVertex2f(0, 0);
        glVertex2f(playerShipSize[0] / 4, playerShipSize[1]);
        glVertex2f(playerShipHalfSize[0], 0);
    } glEnd();
}

GLvoid PlayerShip::cockpit() {
    glColor3f(PlayerShip::COCKPIT_COLOR[0], PlayerShip::COCKPIT_COLOR[1], PlayerShip::COCKPIT_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(playerShipSize[0] * 1 / 40, playerShipSize[1] / 5);
        glVertex2f(playerShipSize[0] * 3 / 40, playerShipSize[1] / 5);
        glVertex2f(playerShipSize[0] / 10, 0.0f);
    } glEnd();
}

GLvoid PlayerShip::leftWing() {
    glColor3f(PlayerShip::SECONDARY_COLOR[0], PlayerShip::SECONDARY_COLOR[1], PlayerShip::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(playerShipHalfSize[0], 0);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::rightWing(GLvoid) {
    glColor3f(PlayerShip::SECONDARY_COLOR[0], PlayerShip::SECONDARY_COLOR[1], PlayerShip::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, playerShipHalfSize[1]);
        glVertex2f(playerShipHalfSize[0], playerShipHalfSize[1]);
    } glEnd();
}

GLvoid PlayerShip::cannon(GLvoid) {
    glColor3f(PlayerShip::PRIMARY_COLOR[0], PlayerShip::PRIMARY_COLOR[1], PlayerShip::PRIMARY_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(playerShipSize[0] * 1 / 40, playerShipSize[1] / 10);
        glVertex2f(playerShipSize[0] / 10, playerShipSize[1] / 10);
        glVertex2f(playerShipSize[0] / 8, 0.0f);
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
    glTranslatef(playerShipSize[0] / 5, playerShipHalfSize[1], 0.0f);
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
            if (this->position[1] + playerHalfHitbox[1] + this->speed < WORLD_BORDERS[3]) {
                this->position[1] += this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::DOWN:
            if (this->position[1] - playerHalfHitbox[1] - this->speed > WORLD_BORDERS[2]) {
                this->position[1] -= this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::LEFT:
            if (this->position[0] - playerHalfHitbox[0] - this->speed > WORLD_BORDERS[0]) {
                this->position[0] -= this->speed;
                hasMoved = true;
            }
            break;
        case MOVE_DIRS::RIGHT:
            if (this->position[0] + playerHalfHitbox[0] + this->speed < WORLD_BORDERS[1]) {
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

    // Swap hitboxes values
    GLfloat tmp = playerHitbox[0];
    playerHitbox[0] = playerHitbox[1];
    playerHitbox[1] = tmp;

    tmp = playerHalfHitbox[0];
    playerHalfHitbox[0] = playerHalfHitbox[1];
    playerHalfHitbox[1] = tmp;

    // Avoid ship clipping through borders
    if (this->position[0] - playerHalfHitbox[0] < WORLD_BORDERS[0])
        this->position[0] += this->speed;
    else if (this->position[0] + playerHalfHitbox[0] > WORLD_BORDERS[1])
        this->position[0] -= this->speed;
    else if (this->position[1] - playerHalfHitbox[1] < WORLD_BORDERS[2])
        this->position[1] += this->speed;
    else if (this->position[1] + playerHalfHitbox[1] > WORLD_BORDERS[3])
        this->position[1] -= this->speed;

    if (abs(this->currentAngle) >= 360) {
        this->currentAngle = 0;
    }
}

std::vector<Bullet*> PlayerShip::fireBullet() {
    std::vector<Bullet*> bullets;

    Bullet* newBullet = this->bullet->clone();

    switch (this->currentAngle) {
        case 0:
            newBullet->setPosition(this->position[0], this->position[1] + playerHalfHitbox[1] + bulletHalfSize[1] + PlayerShip::bulletSpace);
            newBullet->setDirection(MOVE_DIRS::UP);
            break;
        case -90:
        case 270:
            newBullet->setPosition(this->position[0] + playerHalfHitbox[0] + bulletHalfSize[0] + PlayerShip::bulletSpace, this->position[1]);
            newBullet->setDirection(MOVE_DIRS::RIGHT);
            break;
        case -180:
        case 180:
            newBullet->setPosition(this->position[0], this->position[1] - playerHalfHitbox[1] - bulletHalfSize[1] - PlayerShip::bulletSpace);
            newBullet->setDirection(MOVE_DIRS::DOWN);
            break;
        case -270:
        case 90:
            newBullet->setPosition(this->position[0] - playerHalfHitbox[0] - bulletHalfSize[0] - PlayerShip::bulletSpace, this->position[1]);
            newBullet->setDirection(MOVE_DIRS::LEFT);
            break;
    }

    bullets.push_back(newBullet);

    if (this->canFireExtra) {
        Bullet* leftBullet = this->bullet->clone();
        Bullet* rightBullet = this->bullet->clone();

        leftBullet->setDamage(this->bulletDmg / 2);
        rightBullet->setDamage(this->bulletDmg / 2);

        GLfloat xOffset, yOffset;

        switch (this->currentAngle) {
            case 0:
                xOffset = playerHitbox[0] * 9.5f / 40;
                yOffset = playerHitbox[1] / 10 + bulletHalfSize[1] + bulletSpace;

                leftBullet->setPosition(this->position[0] - xOffset, this->position[1] + yOffset);
                rightBullet->setPosition(this->position[0] + xOffset, this->position[1] + yOffset);
                leftBullet->setDirection(MOVE_DIRS::UP);
                rightBullet->setDirection(MOVE_DIRS::UP);
                break;
            case -90:
            case 270:
                xOffset = playerHitbox[0] / 10 + bulletHalfSize[1] + bulletSpace;
                yOffset = playerHitbox[1] * 9.5f / 40;

                leftBullet->setPosition(this->position[0] + xOffset, this->position[1] + yOffset);
                rightBullet->setPosition(this->position[0] + xOffset, this->position[1] - yOffset);
                leftBullet->setDirection(MOVE_DIRS::RIGHT);
                rightBullet->setDirection(MOVE_DIRS::RIGHT);
                break;
            case -180:
            case 180:
                xOffset = playerHitbox[0] * 9.5f / 40;
                yOffset = playerHitbox[1] / 10 + bulletHalfSize[1] + bulletSpace;

                leftBullet->setPosition(this->position[0] + xOffset, this->position[1] - yOffset);
                rightBullet->setPosition(this->position[0] - xOffset, this->position[1] - yOffset);
                leftBullet->setDirection(MOVE_DIRS::DOWN);
                rightBullet->setDirection(MOVE_DIRS::DOWN);
                break;
            case -270:
            case 90:
                xOffset = playerHitbox[0] / 10 + bulletHalfSize[1] + bulletSpace;
                yOffset = playerHitbox[1] * 9.5f / 40;

                leftBullet->setPosition(this->position[0] - xOffset, this->position[1] - yOffset);
                rightBullet->setPosition(this->position[0] - xOffset, this->position[1] + yOffset);
                leftBullet->setDirection(MOVE_DIRS::LEFT);
                rightBullet->setDirection(MOVE_DIRS::LEFT);
                break;
        }

        bullets.insert(bullets.end(), {leftBullet, rightBullet});
    }

    return bullets;
}