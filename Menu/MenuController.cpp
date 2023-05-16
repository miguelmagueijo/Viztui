//
// Created by Miguel Magueijo on 15/05/2023.
//

#include "MenuController.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependacies/stb_image.h"

// 0 -> controls, 1 -> enemies, 2 -> pickups
GLint helpCurrTab = 0;
std::vector<GLint> lvlScores = {};

unsigned int textureID;

GLvoid loadImageTexture(char* imgPath) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // OpenGL expects x:0 y:0 to be on bottom left of image, but images have x:0 y:0 on top left
    stbi_set_flip_vertically_on_load(true);

    // Read file data
    int width, height, nrChannels;
    unsigned char *imgData = stbi_load(imgPath, &width, &height, &nrChannels, 0);

    if (!imgData) {
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    stbi_image_free(imgData);
}

GLvoid drawImgOnEntireWorld(char* imgPath) {
    loadImageTexture(imgPath);

    glEnable(GL_TEXTURE_2D); // enable texturing 2D
    glBindTexture(GL_TEXTURE_2D, textureID); // set opengl to use texture stored in textureID

    // TexCoord S is X, T is Y, R is Z
    glBegin(GL_QUADS); {
        // Bottom Left
        glTexCoord2f(0.0, 0.0);
        glVertex3f(WORLD_BORDERS[0], WORLD_BORDERS[2], 0.0f);

        // Top Left
        glTexCoord2f(0.0, 1.0);
        glVertex3f(WORLD_BORDERS[0], WORLD_BORDERS[3], 0.0f);

        // Top Right
        glTexCoord2f(1.0, 1.0);
        glVertex3f(WORLD_BORDERS[1], WORLD_BORDERS[3], 0.0f);

        // Bottom Right
        glTexCoord2f(1.0, 0.0);
        glVertex3f(WORLD_BORDERS[1], WORLD_BORDERS[2], 0.0f);
    }glEnd();

    glDisable(GL_TEXTURE_2D); // no need to texturize anything else
    glBindTexture(GL_TEXTURE_2D, 0); // unload texture
}

/* #####################################################################################################################
 * DRAW CALLBACKS
 * #####################################################################################################################
 */
GLvoid drawMainMenu() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(WORLD_BORDERS[0], WORLD_BORDERS[1], WORLD_BORDERS[2], WORLD_BORDERS[3]);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    drawImgOnEntireWorld("../MenuTextures/MainMenu.png");

    glutSwapBuffers();
}

GLvoid drawHelpMenu() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(WORLD_BORDERS[0], WORLD_BORDERS[1], WORLD_BORDERS[2], WORLD_BORDERS[3]);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    switch (helpCurrTab) {
        case 0:
            drawImgOnEntireWorld("../MenuTextures/HelpControls.png");
            break;
        case 1:
            drawImgOnEntireWorld("../MenuTextures/HelpEnemies.png");
            break;
        case 2:
            drawImgOnEntireWorld("../MenuTextures/HelpPickups.png");
            break;
        default:
            drawImgOnEntireWorld("../MenuTextures/HelpControls.png");
            break;
    }

    glutSwapBuffers();
}

GLvoid drawNormalLvlMenu() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(WORLD_BORDERS[0], WORLD_BORDERS[1], WORLD_BORDERS[2], WORLD_BORDERS[3]);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    switch (lvlScores.size()) {
        case 0:
            drawImgOnEntireWorld("../MenuTextures/NormalMenu_0.png");
            break;
        case 1:
            drawImgOnEntireWorld("../MenuTextures/NormalMenu_1.png");
            break;
        case 2:
            drawImgOnEntireWorld("../MenuTextures/NormalMenu_2.png");
            break;
        case 3:
            drawImgOnEntireWorld("../MenuTextures/NormalMenu_3.png");
            break;
        default:
            std::cout << "[DEBUG] More scores registers than levels!" << std::endl;
            drawImgOnEntireWorld("../MenuTextures/NormalMenu_0.png");
            break;
    }

    glutSwapBuffers();
}



/* #####################################################################################################################
 * KEYBOARD CALLBACKS
 * #####################################################################################################################
 */
GLvoid keyboardMainMenu(unsigned char key, int x, int y) {
    switch (key) {
        case 'N':
        case 'n':
            openNormalLvlMenu();
            break;
        case 'E':
        case 'e':
            // TODO - send player to endless level menu
            std::cout << "[DEBUG] Endless level menu redirect not implemented" << std::endl;
            break;
        case 'O':
        case 'o':
            // TODO - send player to option menu
            std::cout << "[DEBUG] Option menu redirect not implemented" << std::endl;
            break;
        case 'H':
        case 'h':
            openHelpMenu();
            break;
        case 27:
            exit(0);
    }
}

GLvoid keyboardHelpMenu(unsigned char key, int x, int y) {
    switch (key) {
        case 9: // tab, iterates tabs
            if (++helpCurrTab > 2) {
                helpCurrTab = 0;
            }
            glutPostRedisplay();
            break;
        case 'C':
        case 'c':
            helpCurrTab = 0;
            glutPostRedisplay();
            break;
        case 'E':
        case 'e':
            helpCurrTab = 1;
            glutPostRedisplay();
            break;
        case 'P':
        case 'p':
            helpCurrTab = 2;
            glutPostRedisplay();
            break;
        case 'B':
        case 'b':
        case 27:
            openMainMenu();
    }
}

GLvoid keyboardNormalLvlMenu(unsigned char key, int x, int y) {
    switch (key) {
        case '-':
            lvlScores.push_back(9999);
            glutPostRedisplay();
            break;
        case '.':
            lvlScores.clear();
            glutPostRedisplay();
            break;
        case '1':
            helpCurrTab = 0;
            drawHelpMenu();
            break;
        case '2':
            if (lvlScores.empty())
                break;

            break;
        case '3':
            if (lvlScores.size() < 2)
                break;

            break;
        case 'B':
        case 'b':
        case 27:
            openMainMenu();
    }
}

/* #####################################################################################################################
 * Open menus methods
 * #####################################################################################################################
 */
GLvoid openMainMenu() {
    glutDisplayFunc(drawMainMenu);
    glutKeyboardFunc(keyboardMainMenu);
    glutIdleFunc(nullptr);

    glutPostRedisplay();
}

GLvoid openHelpMenu() {
    glutDisplayFunc(drawHelpMenu);
    glutKeyboardFunc(keyboardHelpMenu);
    helpCurrTab = 0; // opens controls by default
    glutIdleFunc(nullptr);

    glutPostRedisplay();
}

GLvoid openNormalLvlMenu() {
    glutDisplayFunc(drawNormalLvlMenu);
    glutKeyboardFunc(keyboardNormalLvlMenu);
    glutIdleFunc(nullptr);

    glutPostRedisplay();
}