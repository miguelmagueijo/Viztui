//
// Created by Miguel Magueijo on 04/05/2023.
//

#include "EnemyMiner.h"

EnemyMiner::EnemyMiner(GLfloat x, GLfloat y, GLfloat hp) : Enemy(x, y, hp) {
    this->setPickup(new PickupEnemyMine(2));
}

GLvoid EnemyMiner::body() {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] / 2);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, Enemy::SIZE[1] / 2);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid EnemyMiner::cockpit() {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] * 3 / 10);
        glVertex2f(Enemy::SIZE[0] / 10, Enemy::SIZE[1] * 3 / 10);
        glVertex2f(Enemy::SIZE[0] / 10, 0);
    } glEnd();
}

GLvoid EnemyMiner::wing() {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 3 / 10, Enemy::SIZE[1]);
        glVertex2f(Enemy::SIZE[0] * 3 / 10, 0);
    } glEnd();
}

GLvoid EnemyMiner::mine() {
    glColor3f(0.22f, 0.72f, 0.33f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, Enemy::SIZE[1] * 2 / 5);
        glVertex2f(Enemy::SIZE[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid EnemyMiner::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - Enemy::HALF_SIZE[0], this->position[1] - Enemy::HALF_SIZE[1], 0);

    this->wing(); // draws left wing

    glPushMatrix(); // Save translation matrix;

    glTranslatef(Enemy::SIZE[0] * 3 / 10, 0, 0);
    this->body();

    glTranslatef(0, Enemy::SIZE[1] * 3 / 5, 0);
    this->mine();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 9 / 20, Enemy::SIZE[1] / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(Enemy::SIZE[0] * 7 / 10, 0, 0);
    this->wing(); // draw right wing

    glPopMatrix();
    glPopMatrix();
}