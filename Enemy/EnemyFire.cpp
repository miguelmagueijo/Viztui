//
// Created by Miguel Magueijo on 03/05/2023.
//

#include "EnemyFire.h"

EnemyFire::EnemyFire(GLfloat x, GLfloat y, GLfloat hp) : Enemy(x, y, hp) {};

GLvoid EnemyFire::body() {
    if (!this->hasPickup)
        glColor3f(Enemy::PRIMARY_COLOR[0], Enemy::PRIMARY_COLOR[1], Enemy::PRIMARY_COLOR[2]);
    else
        glColor3f(Enemy::SPECIAL_PRIMARY_COLOR[0], Enemy::SPECIAL_PRIMARY_COLOR[1], Enemy::SPECIAL_PRIMARY_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] * 4 / 5);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, Enemy::SIZE[1] * 4 / 5);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid EnemyFire::cockpit() {
    glColor3f(Enemy::COCKPIT_COLOR[0], Enemy::COCKPIT_COLOR[1], Enemy::COCKPIT_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] / 10, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] / 10, 0);
    } glEnd();
}

GLvoid EnemyFire::cannon() {
    glColor3f(Enemy::SECONDARY_COLOR[0], Enemy::SECONDARY_COLOR[1], Enemy::SECONDARY_COLOR[2]);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] / 5);
        glVertex2f(Enemy::SIZE[0] / 10, Enemy::SIZE[1] / 5);
        glVertex2f(Enemy::SIZE[0] / 10, 0);
    } glEnd();
}

GLvoid EnemyFire::leftWing() {
    glColor3f(Enemy::SECONDARY_COLOR[0], Enemy::SECONDARY_COLOR[1], Enemy::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 7 / 10, Enemy::SIZE[1]);
    } glEnd();
}

GLvoid EnemyFire::rightWing() {
    glColor3f(Enemy::SECONDARY_COLOR[0], Enemy::SECONDARY_COLOR[1], Enemy::SECONDARY_COLOR[2]);

    glBegin(GL_TRIANGLES); {
        glVertex2f(Enemy::SIZE[0] * 7 / 10, 0);
        glVertex2f(0, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 7 / 10, Enemy::SIZE[1]);
    } glEnd();
}

GLvoid EnemyFire::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - Enemy::HALF_SIZE[0], this->position[1] - Enemy::HALF_SIZE[1], 0);

    this->leftWing();

    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 3 / 10, 0, 0);
    this->rightWing();

    glTranslatef(0, Enemy::SIZE[1] / 5, 0);
    this->body();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 9 / 20, 0, 0);
    this->cannon();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 9 / 20, Enemy::SIZE[1] * 3 / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPopMatrix();
}