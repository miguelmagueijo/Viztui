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

const extern GLfloat WORLD_BORDERS[4];

enum class MOVE_DIRS { UP, DOWN, LEFT, RIGHT };
enum class GAME_STATE { PLAYING, PAUSED, GAMEOVER };

typedef struct levelinfo {
    // Enemies X space to occupy in world (value between 0-1)
    GLfloat xPerToOcupy;
    // Enemies X space between enemies
    GLfloat enemySpaceX;
    // Enemy max hits on border before moving down
    GLint enemyHitsToDown;
    // Enemy speed move speed when moving in X axis and Y axis
    GLfloat enemySpeed[2];
    // Speed to increment each time enemies move down
    GLfloat enemySpeedIncrement[2];
    // Pickup speed when enemy drops it
    GLfloat pickupSpeed;
    // Number of enemy waves in the level and the size of the next 3 vectors
    GLint numWaves;
    // Enemy to be placed in each line, 0 -> basic, 1 -> fire, 2 -> miner
    std::vector<std::vector<GLint>> enemyTypePerLine;
    // Hp of each enemy per wave, 0 -> basic, 1 -> fire, 2 -> miner
    std::vector<std::vector<GLfloat>> enemyHpPerWave;
    // Number of pickups per wave, 0 -> MoreHp, 1 -> TwoBullets, 3 -> MoreDamage
    std::vector<std::vector<GLint>> pickupsPerWave;
    // Pointer to the next level, nullptr and it's the last level
    struct levelinfo* nextLevel;
} levelinfo;

#endif //VIZTUI_VIZTUI_LIB_H
