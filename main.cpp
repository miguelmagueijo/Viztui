#include "Viztui.lib.h"
#include "./Menu/MenuController.h"
#include "./Level/LevelController.h"

/**
 * Global constants are named in UPPERCASE
 * Local constants are named in camelCase
 * Global and Local variables are named in camelCase
 */

// Window size [Width, Height] and Aspect Ratio
const GLint INITIAL_WINDOW_SIZE[2] = { 720, 720 };
const GLfloat INITIAL_AR = GLfloat(INITIAL_WINDOW_SIZE[0]) / GLfloat(INITIAL_WINDOW_SIZE[1]);

// World Borders by order Left, Right, Bottom, Up
const GLfloat WORLD_BORDERS[4] = {-125, 125, -125, 125 };
// World distance X axis (idx: 0) and Y axis (idx: 1)
const GLfloat WORLD_DISTANCE[2] = { abs(WORLD_BORDERS[1] - WORLD_BORDERS[0]),
                                    abs(WORLD_BORDERS[3] - WORLD_BORDERS[2]) };


// On window resize also resizes world screen and keeps original aspect ratio
GLvoid onWindowResize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Base equation R = W / H
    const float NEW_AR = float(w) / float(h);

    if (NEW_AR < INITIAL_AR) { // mais altura que largura
        const int NEW_HEIGHT = w / INITIAL_AR;
        glViewport(0, (h - NEW_HEIGHT) / 2, w, NEW_HEIGHT);
    } else if (NEW_AR > INITIAL_AR) { // mais largura que altura
        const int NEW_WIDTH = h * INITIAL_AR;
        glViewport((w - NEW_WIDTH) / 2, 0, NEW_WIDTH, h);
    } else {
        glViewport(0, 0, w, h);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(nullptr)); // seed random generator

    // Init glut environment
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set window position in the center of screen
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - INITIAL_WINDOW_SIZE[0] / 2,
                           glutGet(GLUT_SCREEN_HEIGHT) / 2 - INITIAL_WINDOW_SIZE[1] / 2);

    // Set window size
    glutInitWindowSize(INITIAL_WINDOW_SIZE[0], INITIAL_WINDOW_SIZE[1]);

    // Create window and set title
    glutCreateWindow("Viztui - The Space War");

    glutReshapeFunc(onWindowResize);

    //MenuController::openMainMenu();
    LevelController::start(1);

    // run main loop
    glutMainLoop();
    return 0;
}