#include "Viztui.lib.h"
#include "./PlayerShip/PlayerShip.h"
#include "./Bullet/Bullet.h"
#include "./Enemy/Enemy.h"
#include "./Enemy/SoldierTransporter.h"
#include "Bullet/EnemyBullet.h"
#include "Enemy/Fighter.h"
#include "Menu/MainMenu.h"
#include "ElementsUI/HpHeart.h"
#include "Enemy/MineTransporter.h"
#include <cstdlib>
#include <ctime>


const GLint MAX_ENEMY_COUNT_DOWN = 3;

// World Borders by order Left, Right, Bottom, Up
GLfloat worldBorders[4] = { -125, 125, -125, 125 };

// Sizes
GLfloat enemySize[2] = { 20, 10 }; // All enemies are the same size. Size ratio is 2:1 (Size is 20:10)
GLfloat enemyHalfSize[2] = { enemySize[0] / 2, enemySize[1] / 2 };
GLfloat bulletSize[2] = { 2, 5};
GLfloat bulletHalfSize[2] = { bulletSize[0] / 2, bulletSize[1] / 2 };

GLboolean gameOver = false;
GLboolean frameTimerUp = false;
GLboolean needsDraw = false;
GLboolean areEnemiesMovingLeft = false;
GLboolean playerCanFire = true;
GLboolean enemyCanFire = true;
MOVE_DIRS enemyMoveDir = MOVE_DIRS::RIGHT;
GLint currEnemyCountDown = 0;


PlayerShip* playerShip = new PlayerShip((worldBorders[0] + abs(worldBorders[1] - worldBorders[0]) / 2), ( worldBorders[2] + playerShipSize[1] / 2 ) + 5, 4, 3);

std::vector<HpHeart*> playerHpHeartsUI;

/**
 * BASICAMENTE A CENA DA MINA DO INIMIGO É UM PICK-UP QUE TIRA VIDA
 * Fazer um metodo que gera inimigos consoante o dado, por linha e colunas
 * Fazer pickups
 * Usar scale para texto
 * fazer metodo para dizer se está fora do mundo
 */

std::vector<Enemy*> enemies;
std::vector<Bullet*> bullets;
std::vector<Pickup*> pickups;

GLvoid enemyFireTimer(GLint value) {
    enemyCanFire = true;
}

GLvoid playerFireTimer(GLint value) {
    playerCanFire = true;
}

GLvoid createEnemies(GLfloat startX, GLfloat startY) {
    enemies.clear();

    GLint nLines = static_cast<GLint>(abs(worldBorders[3] - worldBorders[2]) * 0.3f / (enemySize[1] * 2));
    GLint nCols = static_cast<GLint>(abs(worldBorders[1] - worldBorders[0]) / (enemySize[0] * 2));
    nCols -= nCols / 5 + 1;

    for (GLint i = 0; i < nLines; i++) {
        for (GLint j = 0; j < nCols; j++) {
            // (Ponto inicial ± halfSize) ± ( (size * 2) * col|line)
            enemies.push_back(
                    new MineTransporter(
                            worldBorders[0] + 0.3f + enemySize[0] / 2 + enemySize[0] * 2 * j,
                            worldBorders[3]  - 0.3f - enemySize[1] / 2 - enemySize[1] * 2 * i,
                            2,
                            5
                    )
            );

        }
    }
}


// Function that draws cartesian axis
GLvoid drawAxis() {
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 50.0f);
    } glEnd();

    glBegin(GL_LINES); {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(50.0f, 0.0f);
    } glEnd();
}

GLvoid draw(GLvoid) {
    // Define background color
    glClearColor(0, 0, 0, 255);

    // Clear Color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Select Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Load identity matrix
    glLoadIdentity();

    // Set Projection Type - 2D orthogonal
    gluOrtho2D(worldBorders[0], worldBorders[1], worldBorders[2], worldBorders[3]);

    // Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    playerShip->draw();
    //playerBullet->draw();
    //soldierTransporter->draw();
    //enemyFighter->draw();
    //mineTransporter->draw();

    for(Bullet* b : bullets) {
        b->draw();
    }

    for (Pickup* p : pickups) {
        p->draw();
    }

    for (Enemy* e : enemies) {
        e->draw();
    }

    for (GLshort i = 0; i < playerShip->getHp(); i++) {
        playerHpHeartsUI.at(i)->draw();
    }

    drawAxis();

    glutSwapBuffers();
}

GLvoid idle(GLvoid) {
    GLfloat enemyHitbox[4] = {worldBorders[1], worldBorders[0], worldBorders[3], worldBorders[2]};
    GLfloat *playerShipPosition = playerShip->getPosition();
    GLfloat *enemyPosition, *bulletPosition, *pickupPosition;

    if (frameTimerUp) {
        // Bullets collisions
        for (GLint i = 0; i < bullets.size(); i++) {
            Bullet* b = bullets.at(i);
            bulletPosition = b->getPosition();

            if (b->isFiredByPlayer()) {
                GLboolean hasCollided = false;
                for (GLint j = 0; j < enemies.size(); j++) {
                    enemyPosition = enemies.at(j)->getPosition();

                    if ( !(enemyPosition[1] - enemySize[1] / 2 >= bulletPosition[1] + bulletHalfSize[1] || // inimigo min y > bullet max y
                           enemyPosition[0] - enemySize[0] / 2 >= bulletPosition[0] + bulletHalfSize[0] || // inimigo min x > bullet max x
                           enemyPosition[1] + enemySize[1] / 2 <= bulletPosition[1] - bulletHalfSize[1] || // inimigo max y < bullet min y
                           enemyPosition[0] + enemySize[0] / 2 <= bulletPosition[0] - bulletHalfSize[0]) ) { // inimigo max x < bullet min x

                        std::cout << "Collision bullet with enemy" << std::endl;
                        Enemy* e = enemies.at(j);
                        e->takeDamage(b->getDamage());
                        if (!e->isAlive()) {
                            Pickup* p = e->getPickup();
                            if (p != nullptr) {
                                pickups.push_back(p);
                            }

                            enemies.erase(enemies.begin() + j);
                        }

                        bullets.erase(bullets.begin() + i);

                        hasCollided = true;

                        break;
                    }
                }

                if (hasCollided) continue;

            } else {
                if (!(playerShipPosition[1] - playerShipHalfSize[1] >= bulletPosition[1] + bulletSize[1] / 2 || // inimigo min y > bullet max y
                        playerShipPosition[0] - playerShipHalfSize[0] >= bulletPosition[0] + bulletSize[0] / 2 || // inimigo min x > bullet max x
                        playerShipPosition[1] + playerShipHalfSize[1] <= bulletPosition[1] - bulletSize[1] / 2 || // inimigo max y < bullet min y
                        playerShipPosition[0] + playerShipHalfSize[0] <= bulletPosition[0] - bulletSize[0] / 2)) {

                    playerShip->takeDamage(static_cast<GLint>(b->getDamage()));
                    bullets.erase(bullets.begin() + i);

                    if (!playerShip->isAlive())
                        gameOver = true;

                    continue;
                }
            }

            if (bulletPosition[1] - bulletHalfSize[1] > worldBorders[3] || // bullet min y > world max y
                    bulletPosition[1] + bulletHalfSize[1] < worldBorders[2] || // bullet max y < world min y
                    bulletPosition[0] - bulletHalfSize[0] > worldBorders[1] || // bullet min x > world max x
                    bulletPosition[0] + bulletHalfSize[0] < worldBorders[0]) {
                bullets.erase(bullets.begin() + i);
                std::cout << "Bullet removed because collided with border" << std::endl;
            }
        }

        // Pickup collisions
        for (GLint i = 0; i < pickups.size(); i++) {
            Pickup* p = pickups.at(i);
            pickupPosition = p->getPosition();

            if (!(playerShipPosition[1] - playerShipHalfSize[1] >= pickupPosition[1] || // inimigo min y > bullet max y
                  playerShipPosition[0] - playerShipHalfSize[0] >= pickupPosition[0] || // inimigo min x > bullet max x
                  playerShipPosition[1] + playerShipHalfSize[1] <= pickupPosition[1] || // inimigo max y < bullet min y
                  playerShipPosition[0] + playerShipHalfSize[0] <= pickupPosition[0])) {

                p->playerEffect(playerShip);
                pickups.erase(pickups.begin() + i);

                if (!playerShip->isAlive()) {
                    gameOver = true;
                }

                break;
            }

            if (pickupPosition[1] > worldBorders[3] || // bullet min y > world max y
                pickupPosition[1] < worldBorders[2] || // bullet max y < world min y
                pickupPosition[0] > worldBorders[1] || // bullet min x > world max x
                pickupPosition[0] < worldBorders[0]) {
                pickups.erase(pickups.begin() + i);
                std::cout << "Pickup removed because collided with border" << std::endl;
            }
        }

        // Enemies collisions
        for (Enemy* e : enemies) {
            enemyPosition = e->getPosition();

            if (enemyPosition[0] - enemyHalfSize[0] < enemyHitbox[0])
                enemyHitbox[0] = enemyPosition[0] - enemyHalfSize[0];

            if (enemyPosition[0] + enemyHalfSize[0] > enemyHitbox[1])
                enemyHitbox[1] = enemyPosition[0] + enemyHalfSize[0];

            if (enemyPosition[1] - enemyHalfSize[1] < enemyHitbox[2])
                enemyHitbox[2] = enemyPosition[1] - enemyHalfSize[1];

            if (enemyPosition[1] - enemyHalfSize[1] > enemyHitbox[3])
                enemyHitbox[3] = enemyPosition[1] + enemyHalfSize[1];

            if ( !(enemyPosition[1] - enemySize[1] / 2 >= playerShipPosition[1] + playerShipHalfSize[1] || // inimigo min y > player max y
                   enemyPosition[0] - enemySize[0] / 2 >= playerShipPosition[0] + playerShipHalfSize[0] || // inimigo min x > player max x
                   enemyPosition[1] + enemySize[1] / 2 <= playerShipPosition[1] - playerShipHalfSize[1] || // inimigo max y < player min y
                   enemyPosition[0] + enemySize[0] / 2 <= playerShipPosition[0] - playerShipHalfSize[0]) ) { // inimigo max x < player min x
                std::cout << "Collision between player and enemies" << std::endl;
                gameOver = true;
            }
        }

        // Collision with borders
        if ( (!areEnemiesMovingLeft && enemyHitbox[1] + 2 > worldBorders[1]) ||
             (areEnemiesMovingLeft && enemyHitbox[0] - 2 < worldBorders[0]) ) {
            currEnemyCountDown++;
            areEnemiesMovingLeft = !areEnemiesMovingLeft;
        }

        // Bullets movements
        for (Bullet* b : bullets) {
            b->move();
        }

        // Pickups movements
        for (Pickup* p : pickups) {
            p->move();
        }


        // Enemies movements
        if (currEnemyCountDown == MAX_ENEMY_COUNT_DOWN) {
            enemyMoveDir = MOVE_DIRS::DOWN;
            currEnemyCountDown = 0;
        } else {
            enemyMoveDir = areEnemiesMovingLeft ? MOVE_DIRS::LEFT : MOVE_DIRS::RIGHT;
        }

        for (Enemy* e : enemies) {
            e->move(enemyMoveDir);
        }

        if (enemyCanFire && !enemies.empty()) {
            enemyCanFire = false;

            GLint enemyIndex = rand() % enemies.size();

            enemyPosition = enemies.at(enemyIndex)->getPosition();

            bullets.push_back(new EnemyBullet(enemyPosition[0], enemyPosition[1] - enemyHalfSize[1] - 3, MOVE_DIRS::DOWN, 2, 1));

            glutTimerFunc(2000, enemyFireTimer, 0);
        }


        frameTimerUp = false;
        needsDraw = true;
    }

    if (needsDraw) {
        glutPostRedisplay();
        needsDraw = false;
    }

}

GLvoid keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0); // no need for break because exits program
        case 'W':
        case 'w':
            needsDraw = playerShip->move(MOVE_DIRS::UP);
            break;
        case 'S':
        case 's':
            needsDraw = playerShip->move(MOVE_DIRS::DOWN);
            break;
        case 'A':
        case 'a':
            needsDraw = playerShip->move(MOVE_DIRS::LEFT);
            break;
        case 'D':
        case 'd':
            needsDraw = playerShip->move(MOVE_DIRS::RIGHT);
            break;
        case 'Q':
        case 'q':
            playerShip->rotate(MOVE_DIRS::LEFT);
            needsDraw = true;
            break;
        case 'E':
        case 'e':
            playerShip->rotate(MOVE_DIRS::RIGHT);
            needsDraw = true;
            break;
        case ' ':
            if (playerCanFire) {
                bullets.push_back(playerShip->fireBullet());
                playerCanFire = false;
                glutTimerFunc(350, playerFireTimer, 0);
                needsDraw = true;
            }

    }
}

GLvoid gameTimer(GLint value) {
    frameTimerUp = true;

    if (!gameOver)
        glutTimerFunc(16, gameTimer, 0);
}



int main(int argc, char** argv) {
    srand(time(nullptr));

    GLfloat initialHeartsPosition[2] = {
                                        worldBorders[0] + HpHeart::hpHeartSize[0] + 2,
                                        worldBorders[2] + HpHeart::hpHeartSize[1] + 2
                                    };
    GLfloat spaceXHearts = 2;
    for (GLshort i = 0; i < PlayerShip::getMaxHp(); i++) {
        playerHpHeartsUI.push_back(new HpHeart(initialHeartsPosition[0] + (HpHeart::hpHeartSize[0] + spaceXHearts) * i, initialHeartsPosition[1]));
    }

    // Init glut environment
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set window initial position
    glutInitWindowPosition(20, 20);

    // Set window size
    glutInitWindowSize(850, 850);

    // Create window and set title
    glutCreateWindow("Viztui - The Space War");

    createEnemies(worldBorders[0] + 5, worldBorders[3] - 5);

    // Set display callback
    glutDisplayFunc(draw);

    // Set keyboard callback
    glutKeyboardFunc(keyboard);

    // Set idle function
    glutIdleFunc(idle);

    glutTimerFunc(16, gameTimer, 0);

    // run main loop
    glutMainLoop();
    return 0;
}