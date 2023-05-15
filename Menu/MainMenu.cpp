//
// Created by Miguel Magueijo on 08/05/2023.
//

#include "MainMenu.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependacies/stb_image.h"

unsigned int textureID;

GLvoid loadImage() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    // Reads file
    unsigned char *data = stbi_load("../MenuTextures/MainMenu.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

GLvoid drawImageOnWorld() {
    loadImage();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // TexCoord S is X, T is Y, R is Z
    glBegin(GL_QUADS); {
        // Bottom Left
        glTexCoord2f(0.0, 0.0);
        glVertex3f(worldBorders[0], worldBorders[3], 0.0f);

        // Top Left
        glTexCoord2f(0.0, 1.0);
        glVertex3f(worldBorders[0], worldBorders[2], 0.0f);

        // Top Right
        glTexCoord2f(1.0, 1.0);
        glVertex3f(worldBorders[1], worldBorders[2], 0.0f);

        // Bottom Right
        glTexCoord2f(1.0, 0.0);
        glVertex3f(worldBorders[1], worldBorders[3], 0.0f);
    }glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid MainMenu::draw() {
    glClearColor(0, 0, 0, 255);

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(worldBorders[0], worldBorders[1], worldBorders[2], worldBorders[3]);

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