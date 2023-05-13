#include "Viztui.lib.h"
#include "./PlayerShip/PlayerShip.h"
#include "./Enemy/Enemy.h"
#include "./Enemy/EnemyBasic.h"
#include "Bullet/Bullet.h"
#include "Enemy/EnemyFire.h"
#include "Menu/MainMenu.h"
#include "ElementsUI/HpHeart.h"
#include "Enemy/MineTransporter.h"
#include "Pickup/PickupMoreHp.h"
#include "Pickup/PickupMoreDamage.h"
#include "Pickup/PickupTwoBullets.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <set>


const GLint MAX_ENEMY_COUNT_DOWN = 3;

// Window size [Width, Height]
GLint windowSize[2] = { 850, 850 };
GLfloat halfWindowSize[2] = { static_cast<GLfloat>(windowSize[0] / 2), static_cast<GLfloat>(windowSize[1] / 2) };
// World Borders by order Left, Right, Bottom, Up
GLfloat worldBorders[4] = { -125, 125, -125, 125 };

// Sizes
GLfloat enemySize[2] = { 20, 10 }; // All enemies are the same size. Size ratio is 2:1 (Size is 20:10)
GLfloat enemyHalfSize[2] = { enemySize[0] / 2, enemySize[1] / 2 };

struct gamelevel* currentLevel;
GLboolean gameOver = false; // to be removed
GAME_STATE gameState = GAME_STATE::PLAYING;
GLint currWaveNum = 0;
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

std::set<GLint> idxEnemiesThatFire;

struct gamelevel* level1 = new struct gamelevel;
struct gamelevel* level2 = new struct gamelevel;
//struct level* level3 = new struct level;

GLvoid setupLevels() {
    // Level 1
    level1->enemyBorderHitMax = 3;
    level1->enemySpeed = 2;
    level1->pickupSpeed = 1;
    level1->enemySpeedIncremental = 0.1f;
    level1->occupiedPercentageX = 70;
    level1->numWaves = 1;
    level1->enemyTypePerLine.push_back({ { 0, 0, 0 } });
    level1->enemyHpPerWave.push_back({ { 20, 0, 0 } });
    level1->pickupsPerWave.push_back({ { 0, 1, 0 } });
    level1->nextLevel = level2;

    // Level 2
    level2->enemyBorderHitMax = 3;
    level2->enemySpeed = 2;
    level1->pickupSpeed = 1.25f;
    level2->enemySpeedIncremental = 0.1f;
    level2->occupiedPercentageX = 70;
    level2->numWaves = 2;
    level2->enemyTypePerLine = { { 1, 1, 2 }, { 1, 2, 2 } };
    level2->enemyHpPerWave = { { 20, 30, 0 }, { 20, 30, 0 } };
    level2->pickupsPerWave = { { 1, 1, 0 }, { 1, 0, 0 } };
    level2->nextLevel = nullptr;

    // Level 3
    //level3->nextLevel = nullptr;
}

GLvoid enemyFireTimer(GLint value) {
    enemyCanFire = true;
}

GLvoid playerFireTimer(GLint value) {
    playerCanFire = true;
}

GLvoid createEnemies() {
    enemies.clear();
    GLint nLines = currentLevel->enemyTypePerLine.at(currWaveNum).size();
    GLint nCols = abs(worldBorders[1] - worldBorders[0]) * currentLevel->occupiedPercentageX / 100 / (enemySize[0] * 2);
    std::vector<GLint> idxEnemiesCanDrop; // enemies indexes that can drop pickups
    //nCols -= nCols / 5 + 1;

    for (GLint i = 0; i < nLines; i++) {
        GLint enemyType = currentLevel->enemyTypePerLine.at(currWaveNum).at(i);

        for (GLint j = 0; j < nCols; j++) {
            // (Ponto inicial ± halfSize) ± ( (size * 2) * col|line)
            GLfloat x = worldBorders[0] + 0.3f + enemySize[0] / 2 + enemySize[0] * 2 * j;
            GLfloat y = worldBorders[3]  - 0.3f - enemySize[1] / 2 - enemySize[1] * 2 * i;
            GLint idx = enemies.size();

            switch(enemyType) {
                case 0:
                    enemies.push_back( new EnemyBasic(x, y, currentLevel->enemySpeed, currentLevel->enemyHpPerWave.at(currWaveNum).at(0)) );
                    idxEnemiesCanDrop.push_back(idx);
                    break;
                case 1:
                    enemies.push_back( new EnemyFire(x, y, currentLevel->enemySpeed, currentLevel->enemyHpPerWave.at(currWaveNum).at(1)) );
                    idxEnemiesCanDrop.push_back(idx);
                    idxEnemiesThatFire.insert(idx);
                    break;
                case 2:
                    enemies.push_back( new MineTransporter(x, y, currentLevel->enemySpeed, currentLevel->enemyHpPerWave.at(currWaveNum).at(2)) );
                    break;
                default:
                    throw std::invalid_argument("Bad enemy type TODO");
            }
        }
    }

    if (!idxEnemiesCanDrop.empty()) {
        std::vector<GLint> currPickupsWave = currentLevel->pickupsPerWave.at(currWaveNum);

        for (GLint i = 0; i < currPickupsWave.size(); i++) {
            GLboolean breakLoop = false;
            GLint num = currPickupsWave.at(i);
            Pickup * p;

            switch (i) {
                case 0:
                    p = new PickupMoreHp(MOVE_DIRS::DOWN, currentLevel->pickupSpeed);
                    break;
                case 1:
                    p = new PickupTwoBullets(MOVE_DIRS::DOWN, currentLevel->pickupSpeed);
                    break;
                case 2:
                    p = new PickupMoreDamage(MOVE_DIRS::DOWN, currentLevel->pickupSpeed);
                    break;
                default:
                    throw std::invalid_argument("Bad pickup");
            }

            for (GLint j = 0; j < num; j++) {
                if (idxEnemiesCanDrop.empty()) {
                    breakLoop = true;
                    break;
                }

                GLint v = rand() % idxEnemiesCanDrop.size();

                std::cout << "[DEBUG] Pickup type " << i << " on enemy idx " << idxEnemiesCanDrop.at(v) << std::endl;

                enemies.at(idxEnemiesCanDrop.at(v))->setPickup(p);
                idxEnemiesCanDrop.erase(idxEnemiesCanDrop.begin() + v);
            }

            if (breakLoop) break;
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

            if (!b->damagesPlayer()) {
                GLboolean hasCollided = false;
                for (GLint j = 0; j < enemies.size(); j++) {
                    Enemy* e = enemies.at(j);
                    enemyPosition = e->getPosition();

                    if ( !(enemyPosition[1] - enemySize[1] / 2 >= bulletPosition[1] + bulletHalfSize[1] || // inimigo min y > bullet max y
                           enemyPosition[0] - enemySize[0] / 2 >= bulletPosition[0] + bulletHalfSize[0] || // inimigo min x > bullet max x
                           enemyPosition[1] + enemySize[1] / 2 <= bulletPosition[1] - bulletHalfSize[1] || // inimigo max y < bullet min y
                           enemyPosition[0] + enemySize[0] / 2 <= bulletPosition[0] - bulletHalfSize[0]) ) { // inimigo max x < bullet min x

                        std::cout << "Collision bullet with enemy" << b->getDamage() << std::endl;


                        e->takeDamage(b->getDamage());
                        if (!e->isAlive()) {
                            if (e->dropsPickup()) {
                                std::cout << "here" << std::endl;
                                pickups.push_back(e->getPickup());
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

                    playerShip->takeDamage(static_cast<GLshort>(b->getDamage()));
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

            Bullet* b = new Bullet(enemyPosition[0], enemyPosition[1] - enemyHalfSize[1] - 3, MOVE_DIRS::DOWN, false);
            b->setDamage(1);
            b->setSpeed(2);

            bullets.push_back(b);

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
                std::vector<Bullet*> playerBullets = playerShip->fireBullet();
                bullets.insert(bullets.end(), playerBullets.begin(), playerBullets.end());
                playerCanFire = false;
                glutTimerFunc(350, playerFireTimer, 0);
                needsDraw = true;
            }
            break;
        case 'p':
            gameOver = true;
            break;

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
    glutInitWindowSize(windowSize[0], windowSize[1]);

    // Create window and set title
    glutCreateWindow("Viztui - The Space War");

    setupLevels();
    currentLevel = level1;

    createEnemies();

    // Set display callback
    glutDisplayFunc(draw);

    // Set keyboard callback
    //glutKeyboardFunc(MainMenu::keyboard);
    glutKeyboardFunc(keyboard);

    // Set idle function
    //glutIdleFunc(MainMenu::idle);
    glutIdleFunc(idle);

    glutTimerFunc(16, gameTimer, 0);

    // run main loop
    glutMainLoop();
    return 0;
}