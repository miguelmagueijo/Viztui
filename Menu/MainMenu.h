//
// Created by Miguel Magueijo on 08/05/2023.
//

#pragma once
#ifndef VIZTUI_MAINMENU_H
#define VIZTUI_MAINMENU_H

#include "../Viztui.lib.h"
#include <sstream>

class MainMenu {
public:
    static GLvoid draw();
    static GLvoid idle();
    static GLvoid keyboard(unsigned char key, int x, int y);
};


#endif //VIZTUI_MAINMENU_H
