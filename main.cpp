#include "Viztui.lib.h"
#include "./PlayerShip/PlayerShip.h"
#include "./Bullet/PlayerBullet.h"
#include "./Enemy/SoldierTransporter.h"
#include "./Enemy/Fighter.h"
#include "./Enemy/MineTransporter.h"

// Left, Right, Bottom, Up
const GLfloat worldBorders[4] = { -125, 125, -125, 125 };

PlayerShip* playerShip = new PlayerShip(0, -50);
PlayerBullet* playerBullet = new PlayerBullet(0, -30);
SoldierTransporter* soldierTransporter = new SoldierTransporter(0, 0);
Fighter* enemyFighter = new Fighter(-30, 0);
MineTransporter* mineTransporter = new MineTransporter(30, 0);

// Function that draws cartesian axis
GLvoid drawAxis() {
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 50.0f);
    } glEnd();

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(50.0f, 0.0f);
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

    // Set Projection Type - 2D orthogonal
    gluOrtho2D(worldBorders[0], worldBorders[1], worldBorders[2], worldBorders[3]);

    // Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    playerShip->draw();
    playerBullet->draw();
    soldierTransporter->draw();
    enemyFighter->draw();
    mineTransporter->draw();

    drawAxis();

    glutSwapBuffers();
}

GLvoid keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}
#include "./Enemy/SoldierTransporter.h"
int main(int argc, char** argv) {
    // Init Window System
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    // Define Window Start Position
    glutInitWindowPosition(20, 20);

    // Define Window Size
    glutInitWindowSize(850, 850);

    // Create Window with Name
    glutCreateWindow("Viztui - The Space War");

    // set display callback
    glutDisplayFunc(draw);

    // set keyboard callback
    glutKeyboardFunc(keyboard);

    // run main loop
    glutMainLoop();
    return 0;
}