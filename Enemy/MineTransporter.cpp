//
// Created by Miguel Magueijo on 04/05/2023.
//

#include "MineTransporter.h"

// Size ratio is 20:10 (2:1)
GLfloat mineTransporterSize[2] = { 20, 10 };

MineTransporter::MineTransporter(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp) {
    this->position[0] = x;
    this->position[1] = y;
    this->speed = speed;
    this->hp = hp;
}

MineTransporter::MineTransporter() : MineTransporter(0, 0, 2, 20) {}

MineTransporter::MineTransporter(GLfloat x, GLfloat y) : MineTransporter(x, y, 2, 20) {}

MineTransporter::MineTransporter(GLfloat x, GLfloat y, GLfloat speed) : MineTransporter(x, y, speed, 20) {}

MineTransporter::~MineTransporter() {}

GLvoid MineTransporter::body(GLvoid) {
    glColor3f(0.87f, 0.44f, 0.44f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, mineTransporterSize[1] / 2);
        glVertex2f(mineTransporterSize[0] * 2 / 5, mineTransporterSize[1] / 2);
        glVertex2f(mineTransporterSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid MineTransporter::cockpit(GLvoid) {
    glColor3f(0.34f, 0.60f, 1.00f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, mineTransporterSize[1] * 3 / 10);
        glVertex2f(mineTransporterSize[0] / 10, mineTransporterSize[1] * 3 / 10);
        glVertex2f(mineTransporterSize[0] / 10, 0);
    } glEnd();
}

GLvoid MineTransporter::wing(GLvoid) {
    glColor3f(0.29f, 0.31f, 0.76f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, mineTransporterSize[1]);
        glVertex2f(mineTransporterSize[0] * 3 / 10, mineTransporterSize[1]);
        glVertex2f(mineTransporterSize[0] * 3 / 10, 0);
    } glEnd();
}

GLvoid MineTransporter::mine(GLvoid) {
    glColor3f(0.22f, 0.72f, 0.33f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, mineTransporterSize[1] * 2 / 5);
        glVertex2f(mineTransporterSize[0] * 2 / 5, mineTransporterSize[1] * 2 / 5);
        glVertex2f(mineTransporterSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid MineTransporter::draw(GLvoid) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - mineTransporterSize[0] / 2, this->position[1] - mineTransporterSize[1] / 2, 0);

    this->wing(); // draws left wing

    glPushMatrix(); // Save translation matrix;

    glTranslatef(mineTransporterSize[0] * 3 / 10, 0, 0);
    this->body();

    glTranslatef(0, mineTransporterSize[1] * 3 / 5, 0);
    this->mine();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(mineTransporterSize[0] * 9 / 20, mineTransporterSize[1] / 10, 0);
    this->cockpit();

    glPopMatrix();
    glPushMatrix();

    glTranslatef(mineTransporterSize[0] * 7 / 10, 0, 0);
    this->wing(); // draw right wing

    glPopMatrix();
    glPopMatrix();
}

GLvoid MineTransporter::move(MOVE_DIRECTIONS dir) {
    switch(dir) {
        case MOVE_DIRECTIONS::UP:
            this->position[1] += this->speed;
            break;
        case MOVE_DIRECTIONS::DOWN:
            this->position[1] -= this->speed;
            break;
        case MOVE_DIRECTIONS::LEFT:
            this->position[0] -= this->speed;
            break;
        case MOVE_DIRECTIONS::RIGHT:
            this->position[0] += this->speed;
            break;
    }
}

GLfloat* MineTransporter::getPosition(GLvoid) {
    return this->position;
}

GLvoid MineTransporter::takeDamage(GLfloat dmg) {
    this->hp -= dmg;
}

GLboolean MineTransporter::isAlive(GLvoid) {
    return this->hp > 0;
}