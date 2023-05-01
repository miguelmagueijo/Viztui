//
// Created by migue on 30/04/2023.
//

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

#endif //VIZTUI_VIZTUI_LIB_H
