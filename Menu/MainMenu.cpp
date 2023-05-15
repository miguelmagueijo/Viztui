//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "MainMenu.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependacies/stb_image.h"

unsigned int textureID;

GLvoid loadImage(char* imgPath) {
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    stbi_image_free(imgData);
}

GLvoid drawImageOnWorld() {
    loadImage("../MenuTextures/MainMenu.png");

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

GLvoid MainMenu::draw() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(WORLD_BORDERS[0], WORLD_BORDERS[1], WORLD_BORDERS[2], WORLD_BORDERS[3]);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    drawImageOnWorld();

    glutSwapBuffers();
}

GLvoid MainMenu::idle() {}

GLvoid MainMenu::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'N':
        case 'n':
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

            break;
        case 27:
            exit(0);
    }
}