//
// Created by Miguel Magueijo on 09/05/2023.
//

#include "PickupEnemyMine.h"

PickupEnemyMine::PickupEnemyMine(GLint dmg) : Pickup() {
    this->setDamage(2);
}

GLvoid PickupEnemyMine::setDamage(GLint d) {
    if (d <= 0) throw std::invalid_argument("Pickup (EnemyMine) damage needs to be greater than 0");

    this->damage = d;
}

GLvoid PickupEnemyMine::body() {
    glColor3f(0.22f, 0.72f, 0.33f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1]);
        glVertex2f(pickupSize[0], pickupSize[1]);
        glVertex2f(pickupSize[0], 0);
    } glEnd();
}

GLvoid PickupEnemyMine::plate() {
    glColor3f(0.49f, 0.49f, 0.49f);

    glBegin(GL_QUADS); {
        glVertex2f(0, 0);
        glVertex2f(0, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] * 2 / 5, pickupSize[1] * 3 / 7);
        glVertex2f(pickupSize[0] * 2 / 5, 0);
    } glEnd();
}

GLvoid PickupEnemyMine::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(this->position[0] - pickupHalfSize[0], this->position[1] - pickupHalfSize[1], 0);

    this->body();

    glPushMatrix();

    glTranslatef(pickupSize[0] * 3 / 10, pickupSize[1] * 2 / 7, 0);
    this->plate();

    glPopMatrix();
    glPopMatrix();
}

GLvoid PickupEnemyMine::playerEffect(PlayerShip *playerShip) {
    playerShip->takeDamage(this->damage);
}

PickupEnemyMine* PickupEnemyMine::clone() {
    return new PickupEnemyMine(*this);
}