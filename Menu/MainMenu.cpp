//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "MainMenu.h"

GLvoid showText(std::string text, GLfloat xPosScreen, GLfloat yPosScreen, GLboolean horizontalCentered) {
    std::stringstream buffer;
    char c;

    buffer.str(text);
    buffer.clear();

    GLint textWidth = 0;
    if (horizontalCentered) {
        for (char cBuffer : buffer.str()) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, cBuffer);
        }
    }


    glRasterPos2f(-(textWidth / 2) + xPosScreen, yPosScreen);

    while(buffer.get(c)) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

GLvoid MainMenu::draw() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(worldBorders[0], worldBorders[1], worldBorders[2], worldBorders[3]);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    showText("Viztui", halfWindowSize[0], halfWindowSize[1] + halfWindowSize[1] * 3 / 5, true);
    showText("The Space War", halfWindowSize[0], halfWindowSize[1] + halfWindowSize[1] * 2.5 / 5, true);

    showText("(S)tory mode", halfWindowSize[0], halfWindowSize[1] + halfWindowSize[1] * 1 / 5, true);
    showText("(E)ndless Level", halfWindowSize[0], halfWindowSize[1], true);
    showText("(O)ptions", halfWindowSize[0], halfWindowSize[1] - halfWindowSize[1] * 1 / 5, true);
    showText("(ESC) Exit", halfWindowSize[0], halfWindowSize[1] - halfWindowSize[1] * 3 / 5, true);


    glutSwapBuffers();
}

GLvoid MainMenu::idle() {}

GLvoid MainMenu::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'S':
        case 's':
            break;
        case 'I':
        case 'i':
            break;
        case 'O':
        case 'o':
            break;
        case 'A':
        case 'a':
            break;
        case 27:
            exit(0);
    }
}