#include "Viztui.lib.h"
#include "./PlayerShip/PlayerShip.h"
#include "./Bullet/PlayerBullet.h"
#include "./Enemy/Enemy.h"
#include "./Enemy/SoldierTransporter.h"
#include "./Enemy/Fighter.h"
#include "./Enemy/MineTransporter.h"

// Left, Right, Bottom, Up
const GLfloat worldBorders[4] = { -125, 125, -125, 125 };
const GLfloat enemySize[2] = { 20, 10 }; // All enemies are the same size. Size ratio is 2:1 (Size is 20:10)

GLboolean needsDraw = false;

PlayerShip* playerShip = new PlayerShip(0, 0);
/*PlayerBullet* playerBullet = new PlayerBullet(0, -30);
SoldierTransporter* soldierTransporter = new SoldierTransporter(0, 0);
Fighter* enemyFighter = new Fighter(-30, 0);
MineTransporter* mineTransporter = new MineTransporter(30, 0);*/

std::vector<SoldierTransporter*> enemies;

GLvoid createEnemies(GLfloat startX, GLfloat startY) {
    enemies.clear();

    GLint nLines = static_cast<GLint>(abs(worldBorders[3] - worldBorders[2]) * 0.3f / (enemySize[1] * 2));
    GLint nCols = static_cast<GLint>(abs(worldBorders[1] - worldBorders[0]) / (enemySize[0] * 2));
    nCols -= nCols / 5 + 1;

    for (GLint i = 0; i < nLines; i++) {
        for (GLint j = 0; j < nCols; j++) {
            // (Ponto inicial ± halfSize) ± ( (size * 2) * col|line)
            enemies.push_back(
                    new SoldierTransporter(
                            worldBorders[0] + 0.3f + enemySize[0] / 2 + enemySize[0] * 2 * j,
                            worldBorders[3]  - 0.3f - enemySize[1] / 2 - enemySize[1] * 2 * i,
                            2,
                            30
                    )
            );

        }
    }
}


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
    //playerBullet->draw();
    //soldierTransporter->draw();
    //enemyFighter->draw();
    //mineTransporter->draw();

    for (SoldierTransporter* e : enemies) {
        e->draw();
    }

    drawAxis();

    glutSwapBuffers();
}

GLvoid idle(GLvoid) {
    if (needsDraw) {
        glutPostRedisplay();
        needsDraw = false;
    }

}

GLvoid keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0); // no need for break because exits program
        case 'W':
        case 'w':
            needsDraw = playerShip->move(MOVE_DIRS::UP);
            break;
        case 'S':
        case 's':
            needsDraw = playerShip->move(MOVE_DIRS::DOWN);
            break;
        case 'A':
        case 'a':
            needsDraw = playerShip->move(MOVE_DIRS::LEFT);
            break;
        case 'D':
        case 'd':
            needsDraw = playerShip->move(MOVE_DIRS::RIGHT);
            break;
        case 'Q':
        case 'q':
            playerShip->rotate(true);
            needsDraw = true;
            break;
        case 'E':
        case 'e':
            playerShip->rotate(false);
            needsDraw = true;
            break;
    }
}

int main(int argc, char** argv) {
    // Init glut environment
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set window initial position
    glutInitWindowPosition(20, 20);

    // Set window size
    glutInitWindowSize(850, 850);

    // Create window and set title
    glutCreateWindow("Viztui - The Space War");

    createEnemies(worldBorders[0] + 5, worldBorders[3] - 5);

    // Set display callback
    glutDisplayFunc(draw);

    // Set keyboard callback
    glutKeyboardFunc(keyboard);

    // Set idle function
    glutIdleFunc(idle);

    // run main loop
    glutMainLoop();
    return 0;
}