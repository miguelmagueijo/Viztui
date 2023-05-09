//
// Created by Miguel Magueijo on 09/05/2023.
//

#ifndef VIZTUI_HPHEART_H
#define VIZTUI_HPHEART_H

#include "../Viztui.lib.h"

class HpHeart {
private:
    GLfloat position[2] { 0, 0 };

    GLvoid leftArcTriangle();
    GLvoid rightArcTriangle();
    GLvoid bottomTriangle();

public:
    static GLfloat hpHeartSize[2]; // Size ratio is 4:5
    static GLfloat hpHeartHalfSize[2];

    HpHeart(GLfloat x, GLfloat y);
    ~HpHeart() = default;

    GLvoid draw();
};


#endif //VIZTUI_HPHEART_H
