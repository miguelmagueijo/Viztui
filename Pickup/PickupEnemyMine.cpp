//
// Created by Miguel Magueijo on 09/05/2023.
//

#include "PickupEnemyMine.h"

GLfloat PickupEnemyMine::size[2] = { 8, 4 };
GLfloat PickupEnemyMine::halfSize[2] = { PickupEnemyMine::size[0] / 2, PickupEnemyMine::size[1] / 2 };

PickupEnemyMine::PickupEnemyMine(GLfloat x, GLfloat y, MOVE_DIRS dir, GLfloat speed) : Pickup(x, y, dir, speed) {
    this->damage = 2; // default damage value
}

GLvoid PickupEnemyMine::setDamage(GLshort d) {
    if (d < 0) throw std::invalid_argument("Bad mine damage, needs to be >=0.");

    this->damage = d;
}

GLvoid PickupEnemyMine::body() {
    glColor3f(0.22f, 0.72f, 0.33f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupEnemyMine::size[1]);
        glVertex2f(PickupEnemyMine::size[0], PickupEnemyMine::size[1]);
        glVertex2f(PickupEnemyMine::size[0], 0);
    } glEnd();
}

GLvoid PickupEnemyMine::plate() {
    glColor3f(0.49f, 0.49f, 0.49f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, PickupEnemyMine::halfSize[1]);
        glVertex2f(PickupEnemyMine::size[0] / 4, PickupEnemyMine::halfSize[1]);
        glVertex2f(PickupEnemyMine::size[0] / 4, 0);
    } glEnd();
}

GLvoid PickupEnemyMine::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - PickupEnemyMine::halfSize[0], this->position[1] - PickupEnemyMine::halfSize[1], 0);

    this->body();

    glPushMatrix();

    glTranslatef(PickupEnemyMine::size[0] * 3 / 8, PickupEnemyMine::size[1] / 4, 0);
    this->plate();

    glPopMatrix();
    glPopMatrix();
}

GLvoid PickupEnemyMine::playerEffect(PlayerShip *playerShip) {
    playerShip->takeDamage(2);
}

PickupEnemyMine* PickupEnemyMine::clone() {
    return new PickupEnemyMine(*this);
}