//
// Created by migue on 30/04/2023.
//

#pragma once
#ifndef VIZTUI_VIZTUI_LIB_H
#define VIZTUI_VIZTUI_LIB_H

// C++ Libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Freeglut / OpenGL imports that depend on Operating System
// Supports only for Windows and macOS
#if defined(_WIN32) || defined(_WIN64)
#include <GL/freeglut.h>
#elif defined(__APPLE__) || defined(__MACH__) || defined(TARGET_OS_MAC)
#include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#endif

const extern GLfloat WORLD_BORDERS[4];
const extern GLfloat WORLD_DISTANCE[2];

enum class MOVE_DIRS { UP, DOWN, LEFT, RIGHT };
enum class GAME_STATE { PLAYING, PAUSED, GAMEOVER };

#endif //VIZTUI_VIZTUI_LIB_H
