//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "EnemyBasic.h"

EnemyBasic::EnemyBasic(GLfloat x, GLfloat y, GLfloat hp) : Enemy(x, y, hp) {}

GLvoid EnemyBasic::body() {
    if (!this->hasPickup)
        glColor3f(Enemy::PRIMARY_COLOR[0], Enemy::PRIMARY_COLOR[1], Enemy::PRIMARY_COLOR[2]);
    else
        glColor3f(Enemy::SPECIAL_PRIMARY_COLOR[0], Enemy::SPECIAL_PRIMARY_COLOR[1], Enemy::SPECIAL_PRIMARY_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 3 / 5, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 3 / 5, 0);
    } glEnd();
}

GLvoid EnemyBasic::cockpit() {
    glColor3f(Enemy::COCKPIT_COLOR[0], Enemy::COCKPIT_COLOR[1], Enemy::COCKPIT_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] / 5);
        glVertex2f(Enemy::SIZE[0] / 5, Enemy::SIZE[1] / 5);
        glVertex2f(Enemy::SIZE[0] / 5, 0);
    } glEnd();
}

GLvoid EnemyBasic::rocket() {
    glColor3f(Enemy::SECONDARY_COLOR[0], Enemy::SECONDARY_COLOR[1], Enemy::SECONDARY_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] / 5, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] / 5, 0);
    } glEnd();
}

GLvoid EnemyBasic::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - Enemy::HALF_SIZE[0], this->position[1] - Enemy::HALF_SIZE[1], 0);

    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] / 5, 0, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 2 / 5, Enemy::SIZE[1] / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    // Lower Left Rocket
    this->rocket();

    // Upper Left Rocket
    glTranslatef(0, Enemy::SIZE[1] * 3 / 5, 0);
    this->rocket();

    glPopMatrix();
    glPushMatrix();

    // Lower Right Rocket
    glTranslatef(Enemy::SIZE[0] * 4 / 5, 0.0f, 0.0f);
    this->rocket();

    // Upper Right Rocket
    glTranslatef(0.0f, Enemy::SIZE[1] * 3 / 5, 0.0f);
    this->rocket();

    glPopMatrix();
    glPopMatrix();
}