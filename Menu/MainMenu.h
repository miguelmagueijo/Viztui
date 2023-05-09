//
// Created by Miguel Magueijo on 08/05/2023.
//

#ifndef VIZTUI_MAINMENU_H
#define VIZTUI_MAINMENU_H

#include "../Viztui.lib.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu() = default;

    static GLvoid draw(GLvoid);
    static GLvoid idle();
    static GLvoid keyboard(unsigned char key, int x, int y);
};


#endif //VIZTUI_MAINMENU_H
