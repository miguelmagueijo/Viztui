//
// Created by Miguel Magueijo on 09/05/2023.
//

#include "HpHeart.h"

// Size ratio is 4:5
GLfloat HpHeart::hpHeartSize[2] = { 7, 8.75f };
GLfloat HpHeart::hpHeartHalfSize[2] = { HpHeart::hpHeartSize[0] / 2 , HpHeart::hpHeartSize[1] / 2 };

HpHeart::HpHeart(GLfloat x, GLfloat y) {
    this->position[0] = x;
    this->position[1] = y;
}

GLvoid HpHeart::leftArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(0, HpHeart::hpHeartSize[1] * 3 / 5);
        glVertex2f(HpHeart::hpHeartSize[0], 0);
    } glEnd();
}

GLvoid HpHeart::rightArcTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(0, 0);
        glVertex2f(HpHeart::hpHeartSize[0], HpHeart::hpHeartSize[1] * 3 / 5);
        glVertex2f(HpHeart::hpHeartSize[0], 0);
    } glEnd();
}

GLvoid HpHeart::bottomTriangle() {
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES); {
        glVertex2f(HpHeart::hpHeartHalfSize[0], 0);
        glVertex2f(0, HpHeart::hpHeartSize[1] * 2 / 5);
        glVertex2f(HpHeart::hpHeartSize[0], HpHeart::hpHeartSize[1] * 2 / 5);
    } glEnd();
}

GLvoid HpHeart::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - HpHeart::hpHeartHalfSize[0], this->position[1] - HpHeart::hpHeartHalfSize[1], 0);

    this->bottomTriangle();

    glPushMatrix();

    glTranslatef(0, HpHeart::hpHeartSize[1] * 2 / 5, 0);

    this->leftArcTriangle();
    this->rightArcTriangle();

    glPopMatrix();
    glPopMatrix();
}