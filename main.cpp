#include <GL/freeglut.h>
#include "./Bullets/TestBullet.h"

TestBullet* a = new TestBullet();

// Function that draws cartesian axis
GLvoid drawAxis() {
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 3.0f);
    } glEnd();

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(3.0f, 0.0f);
    } glEnd();
}

GLvoid draw(GLvoid) {
    // Define background color
    glClearColor(0, 0, 0, 255);

    // Clear Color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Select Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Load identity matrix
    glLoadIdentity();

    a->draw();

    // Set Projection Type - 2D orthogonal
    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);

    // Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    drawAxis();

    glutSwapBuffers();
}

GLvoid keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

int main(int argc, char** argv) {
    // Init Window System
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    // Define Window Start Position
    glutInitWindowPosition(20, 20);

    // Define Window Size
    glutInitWindowSize(500, 500);

    // Create Window with Name
    glutCreateWindow("Geometric Transformations");

    // set display callback
    glutDisplayFunc(draw);

    // set keyboard callback
    glutKeyboardFunc(keyboard);

    // run main loop
    glutMainLoop();
    return 0;
}