//
// Created by migue on 30/04/2023.
//

#pragma once
#ifndef VIZTUI_VIZTUI_LIB_H
#define VIZTUI_VIZTUI_LIB_H

// C++ Libraries
#include <iostream>
#include <vector>

// Freeglut / OpenGL imports that depend on Operating System
// Support only for Windows and macOS
#if defined(_WIN32) || defined(_WIN64)
#include <GL/freeglut.h>
#elif defined(__APPLE__) || defined(__MACH__) || defined(TARGET_OS_MAC)
#include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#endif

extern GLint windowSize[2];
extern GLfloat halfWindowSize[2];
extern GLfloat worldBorders[4];
extern GLfloat enemySize[2];
extern GLfloat enemyHalfSize[2];

enum class MOVE_DIRS { UP, DOWN, LEFT, RIGHT };
enum class GAME_STATE { PLAYING, PAUSED, OVER };

typedef struct gamelevel {
    GLint occupiedPercentageX;
    GLint enemyBorderHitMax;
    GLfloat enemySpeed;
    GLfloat pickupSpeed;
    GLfloat enemySpeedIncremental; // increments speed for each moves down
    GLint numWaves; // also the size of the next 3 vectors
    std::vector<std::vector<GLint>> enemyTypePerLine; // 0 -> Basic, 1 -> Fire, 2 -> Miner
    std::vector<std::vector<GLfloat>> enemyHpPerWave; // hp of 0 -> basic, 1 -> fire, 2 -> miner
    std::vector<std::vector<GLint>> pickupsPerWave; // idx corresponds to 0 -> MoreHp, 1 -> TwoBullets, 3 -> MoreDamage
    struct gamelevel* nextLevel;
} gamelevel;

#endif //VIZTUI_VIZTUI_LIB_H
