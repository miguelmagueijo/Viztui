//
// Created by Miguel Magueijo on 03/05/2023.
//

#ifndef VIZTUI_ENEMYBASIC_H
#define VIZTUI_ENEMYBASIC_H

#include "../Viztui.lib.h"
#include "Enemy.h"

class EnemyBasic : public Enemy {
private:
    GLvoid body();
    GLvoid cockpit();
    GLvoid rocket();

public:
    EnemyBasic(GLfloat x, GLfloat y, GLfloat speed, GLfloat hp);
    ~EnemyBasic() = default;

    GLvoid draw();
};


#endif //VIZTUI_ENEMYBASIC_H
