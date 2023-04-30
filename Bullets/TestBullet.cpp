//
// Created by migue on 30/04/2023.
//

#include "TestBullet.h"
TestBullet::TestBullet() {

}

GLvoid TestBullet::draw() {
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINES); {
        glVertex2f(0.0f,0.0f);
        glVertex2f(0.0f, 1.0f);

        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.5f, 1.0f);

        glVertex2f(0.5f, 1.0f);
        glVertex2f(0.5f, 0.0f);

        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    }; glEnd();
}