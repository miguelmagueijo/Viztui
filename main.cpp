#include "Viztui.lib.h"
#include "./PlayerShip/PlayerShip.h"
#include "./Enemy/Enemy.h"
#include "./Enemy/EnemyBasic.h"
#include "Bullet/Bullet.h"
#include "Enemy/EnemyFire.h"
#include "UiElements/HpHeart.h"
#include "Enemy/EnemyMiner.h"
#include "Pickup/PickupMoreHp.h"
#include "Pickup/PickupMoreDamage.h"
#include "Pickup/PickupTwoBullets.h"
#include "./Menu/MenuController.h"

/**
 * Global constants are named in UPPERCASE
 * Local constants are named in camelCase
 * Global and Local variables are named in camelCase
 */

// Window size [Width, Height] and Aspect Ratio
const GLint INITIAL_WINDOW_SIZE[2] = { 720, 720 };
const GLfloat INITIAL_AR = GLfloat(INITIAL_WINDOW_SIZE[0]) / GLfloat(INITIAL_WINDOW_SIZE[1]);

// World Borders by order Left, Right, Bottom, Up
const GLfloat WORLD_BORDERS[4] = {-125, 125, -125, 125 };
// World distance X axis (idx: 0) and Y axis (idx: 1)
const GLfloat WORLD_DISTANCE[2] = { abs(WORLD_BORDERS[1] - WORLD_BORDERS[0]), abs(WORLD_BORDERS[3] - WORLD_BORDERS[2]) };
const GLfloat OFFSET_WB_LINES = 0.002f; // space offset to draw world borders lines while playing

struct levelinfo* currLvlInfo;
GAME_STATE gameState = GAME_STATE::PLAYING;
GLint currWaveNum = 0;
GLboolean frameTimerUp = false;
GLboolean needsDraw = false;
GLboolean areEnemiesMovingLeft = false;
GLboolean playerCanFire = true;
GLboolean playerCanRotate = true;
GLboolean enemyCanFire = false;
MOVE_DIRS enemyMoveDir = MOVE_DIRS::RIGHT;
GLint currEnemyCountDown = 0;
GLint waitingForRespawn = false;

std::vector<HpHeart*> playerHpHeartsUI;

PlayerShip* playerShip;
std::vector<Enemy*> enemies;
std::vector<Bullet*> bullets;
std::vector<Pickup*> pickups;

std::vector<GLint> idxEnemiesThatFire;

struct levelinfo* level1 = new struct levelinfo;
struct levelinfo* level2 = new struct levelinfo;
//struct level* level3 = new struct level;

GLvoid setupLevels() {
    // Level 1
    level1->enemySpaceX = Enemy::SIZE[0] * 1.25f;
    level1->enemyHitsToDown = 3;
    level1->enemySpeed[0] = 1;
    level1->enemySpeed[1] = 3;
    level1->enemySpeedIncrement[0] = 0.1f;
    level1->enemySpeedIncrement[0] = 0;
    level1->xPerToOcupy = 0.7f;
    level1->pickupSpeed = 1;
    level1->numWaves = 1;
    level1->enemyTypePerLine = { { 0, 0, 0 } };
    level1->enemyHpPerWave = { { 20, 0, 0 } };
    level1->pickupsPerWave = { { 0, 1, 0 } };
    level1->nextLevel = level2;

    // Level 2
    level2->enemySpaceX = Enemy::SIZE[0] * 1.25f;
    level2->enemyHitsToDown = 3;
    level2->enemySpeed[0] = 1.10f;
    level2->enemySpeed[1] = 3;
    level2->pickupSpeed = 1.25f;
    level2->enemySpeedIncrement[0] = 0.1f;
    level2->enemySpeedIncrement[1] = 0;
    level2->xPerToOcupy = 0.8f;
    level2->numWaves = 2;
    level2->enemyTypePerLine = { { 0, 0, 1 }, { 0, 1, 1 } };
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

GLvoid playerRotateTimer(GLint value) {
    playerCanRotate = true;
}

// Checks if object 1 (pos1, offset1) is colliding with object 2 (pos2, offset2)
GLboolean collissionBetween(const GLfloat* pos1, const GLfloat* offset1, const GLfloat* pos2, const GLfloat* offset2) {
    return !(pos1[1] - offset1[1] >= pos2[1] + offset2[1] || // Object 1 MIN Y >= Object 2 MAX Y
             pos1[1] + offset1[1] <= pos2[1] - offset2[1] || // Object 1 MAX Y <= Object 2 MIN Y
             pos1[0] - offset1[0] >= pos2[0] + offset2[0] || // Object 1 MIN X >= Object 2 MAX X
             pos1[0] + offset1[0] <= pos2[0] - offset2[0]);  // Object 1 MAX X <= Object 2 MIN X
}

// Checks if object (pos, offset) is fully out of any world border (TOP, BOTTOM, RIGHT, LEFT)
GLboolean isOutOfWorldBorders(const GLfloat* pos, const GLfloat* offset) {
    return pos[1] - offset[1] > WORLD_BORDERS[3] || // check top border
           pos[1] + offset[1] < WORLD_BORDERS[2] || // check bottom border
           pos[0] - offset[0] > WORLD_BORDERS[1] || // check right border
           pos[0] + offset[0] < WORLD_BORDERS[0];   // check left border
}

GLvoid createEnemies() {
    // Avoids problems if calling enemies without remaining waves
    if (currWaveNum >= currLvlInfo->numWaves)
        return;

    enemies.clear();

    GLfloat enemySpace[2] = { Enemy::SIZE[0] * 2.0f, Enemy::SIZE[1] * 2.0f };
    GLint nLines = currLvlInfo->enemyTypePerLine.at(currWaveNum).size();
    GLint nCols = WORLD_DISTANCE[0] * currLvlInfo->xPerToOcupy / enemySpace[0];
    std::vector<GLint> idxEnemiesCanDrop; // enemies indexes that can drop pickups

    for (GLint i = 0; i < nLines; i++) {
        const GLint enemyType = currLvlInfo->enemyTypePerLine.at(currWaveNum).at(i);

        for (GLint j = 0; j < nCols; j++) {
            // (Ponto inicial ± halfSize) ± ( (size * 2) * col|line)
            const GLfloat x = WORLD_BORDERS[0] + 0.3f + Enemy::HALF_SIZE[0] / 2 + enemySpace[0] * j;
            const GLfloat y = WORLD_BORDERS[3] - 0.3f - Enemy::HALF_SIZE[1] / 2 - enemySpace[1] * i;
            GLint idx = enemies.size();
            std::vector<GLfloat> enemyHpInfo = currLvlInfo->enemyHpPerWave.at(currWaveNum);

            switch(enemyType) {
                case 0:
                    enemies.push_back( new EnemyBasic(x, y, enemyHpInfo.at(0)) );
                    idxEnemiesCanDrop.push_back(idx);
                    break;
                case 1:
                    enemies.push_back( new EnemyFire(x, y, enemyHpInfo.at(1)) );
                    idxEnemiesCanDrop.push_back(idx);
                    idxEnemiesThatFire.push_back(idx);
                    break;
                case 2:
                    enemies.push_back( new EnemyMiner(x, y, enemyHpInfo.at(2)) );
                    break;
                default:
                    throw std::invalid_argument("Bad enemy type");
            }
        }
    }

    if (!idxEnemiesCanDrop.empty()) {
        std::vector<GLint> currPickupsWave = currLvlInfo->pickupsPerWave.at(currWaveNum);

        for (GLint i = 0; i < currPickupsWave.size(); i++) {
            GLboolean breakLoop = false;
            GLint num = currPickupsWave.at(i);
            Pickup * p;

            switch (i) {
                case 0:
                    p = new PickupMoreHp(1);
                    break;
                case 1:
                    p = new PickupTwoBullets();
                    break;
                case 2:
                    p = new PickupMoreDamage(5);
                    break;
                default:
                    throw std::invalid_argument("Bad pickup type");
            }

            // Set pickup direction and speed
            p->setDirection(MOVE_DIRS::DOWN);
            p->setSpeed(currLvlInfo->pickupSpeed);

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

    waitingForRespawn = false;
}

GLvoid createPlayerShip() {
    playerShip = new PlayerShip(
                (WORLD_BORDERS[0] + abs(WORLD_BORDERS[1] - WORLD_BORDERS[0]) / 2),
                (WORLD_BORDERS[2] + playerShipSize[1] / 2 ) + 5,
                4,
                3
            );
    std::cout << "[DEBUG] PlayerShip created" << std::endl;
}

GLvoid timerSpawnNewWave(int value) {
    createEnemies();
}

GLvoid triggerGameOver() {
    gameState = GAME_STATE::GAMEOVER;
    frameTimerUp = false;
}

GLvoid triggerGameVictory() {
    if (waitingForRespawn)
        return;

    if (!waitingForRespawn && currWaveNum < currLvlInfo->numWaves - 1) {
        currWaveNum++;
        waitingForRespawn = true;
        glutTimerFunc(1500, timerSpawnNewWave, 0);
        return;
    }

    gameState = GAME_STATE::PAUSED;
    std::cout << "You won!" << std::endl;
}

GLvoid drawWorldBorders() {
    glColor3f(0.25f, 0.25f, 0.25f);

    glBegin(GL_LINES); {
        // Left Border
        glVertex2f(WORLD_BORDERS[0] + OFFSET_WB_LINES, WORLD_BORDERS[2]);
        glVertex2f(WORLD_BORDERS[0] + OFFSET_WB_LINES, WORLD_BORDERS[3]);

        // Right Border
        glVertex2f(WORLD_BORDERS[1] - OFFSET_WB_LINES, WORLD_BORDERS[2]);
        glVertex2f(WORLD_BORDERS[1] - OFFSET_WB_LINES, WORLD_BORDERS[3]);

        // Bottom Border
        glVertex2f(WORLD_BORDERS[0], WORLD_BORDERS[2] + OFFSET_WB_LINES);
        glVertex2f(WORLD_BORDERS[1], WORLD_BORDERS[2] + OFFSET_WB_LINES);

        // Top Border
        glVertex2f(WORLD_BORDERS[0], WORLD_BORDERS[3] - OFFSET_WB_LINES);
        glVertex2f(WORLD_BORDERS[1], WORLD_BORDERS[3] - OFFSET_WB_LINES);
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
    gluOrtho2D(WORLD_BORDERS[0] * INITIAL_AR, WORLD_BORDERS[1] * INITIAL_AR, WORLD_BORDERS[2], WORLD_BORDERS[3]);

    // Select modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    drawWorldBorders();

    for (Pickup* p : pickups) {
        p->draw();
    }

    for(Bullet* b : bullets) {
        b->draw();
    }

    for (Enemy* e : enemies) {
        e->draw();
    }

    playerShip->draw();

    for (GLshort i = 0; i < playerShip->getHp(); i++) {
        playerHpHeartsUI.at(i)->draw();
    }

    glutSwapBuffers();
}

GLvoid idle(GLvoid) {
    if (frameTimerUp) {
        GLfloat enemyHitbox[4] = {WORLD_BORDERS[1], WORLD_BORDERS[0], WORLD_BORDERS[3], WORLD_BORDERS[2]};
        GLfloat *playerShipPosition = playerShip->getPosition();

        if (enemies.empty() && !waitingForRespawn) {
            triggerGameVictory();
        }

        /**
         * Collisions
         */
        // Bullet collisions
        for (GLint i = 0; i < bullets.size(); i++) {
            GLboolean hasCollided = false;
            Bullet* b = bullets.at(i);
            GLfloat* bulletPosition = b->getPosition();

            if (b->damagesPlayer()) {
                if (collissionBetween(playerShipPosition, playerShipHalfSize,
                                      bulletPosition, bulletHalfSize)
                ) {

                    playerShip->takeDamage(static_cast<GLshort>(b->getDamage()));
                    bullets.erase(bullets.begin() + i);

                    if (!playerShip->isAlive()) {
                        triggerGameOver();
                        return;
                    }

                    hasCollided = true;
                }
            } else {
                for (GLint j = 0; j < enemies.size(); j++) {
                    Enemy* e = enemies.at(j);
                    GLfloat* enemyPosition = e->getPosition();

                    if (collissionBetween(enemyPosition, Enemy::HALF_SIZE,
                                          bulletPosition, bulletHalfSize)) {
                        std::cout << "[DEBUG] Collision between bullet (idx "<< i <<
                                  ") with enemy (idx "<< j <<") and applied "<< b->getDamage() <<" dmg" << std::endl;

                        e->takeDamage(b->getDamage()); // enemy takes damage

                        if (!e->isAlive()) {
                            // Checks if drops pickup, if so, puts pickup in world
                            if (e->dropsPickup()) {
                                std::cout << "[DEBUG] Enemy (idx " << j << ") dropped a pickup" << std::endl;

                                pickups.push_back(e->getPickup());
                            }

                            enemies.erase(enemies.begin() + j);
                            std::cout << "[DEBUG] Enemy (idx " << j << ") was removed" << std::endl;

                            if (!idxEnemiesThatFire.empty()) {
                                GLint idxToRemove = -1;

                                for (GLint idxEf = 0; idxEf < idxEnemiesThatFire.size(); idxEf++) {
                                    GLint eIdx = idxEnemiesThatFire.at(idxEf);

                                    if (eIdx < j)
                                        continue;
                                    else if (eIdx == j)
                                        idxToRemove = idxEf;
                                    else
                                        idxEnemiesThatFire[idxEf] -= 1;
                                }

                                if (idxToRemove >= 0) {
                                    std::cout << "[DEBUG] Here" << std::endl;
                                    idxEnemiesThatFire.erase(idxEnemiesThatFire.begin() + idxToRemove);
                                    std::cout << "[DEBUG] Removed idx that fire" << std::endl;
                                }
                            }

                        }

                        // Removes bullet because collided
                        bullets.erase(bullets.begin() + i);

                        hasCollided = true;

                        break;
                    }
                }
            }

            // Skips to next bullet because this one has already been removed
            if (hasCollided)
                continue;

            // If didn't collide with enemies or player, check if is outside world, if it is, removes it
            if (isOutOfWorldBorders(bulletPosition, bulletHalfSize)) {
                bullets.erase(bullets.begin() + i);
                std::cout << "[DEBUG] Bullet (idx: "<< i <<") removed because is outside of world" << std::endl;
            }
        }

        // Pickup collisions
        for (GLint i = 0; i < pickups.size(); i++) {
            Pickup* p = pickups.at(i);
            GLfloat* pickupPosition = p->getPosition();

            if (collissionBetween(playerShipPosition, playerShipHalfSize,
                                  pickupPosition, pickupHalfSize)
            ) {
                p->playerEffect(playerShip);
                pickups.erase(pickups.begin() + i);

                if (!playerShip->isAlive()) { // because of mine pickup
                    triggerGameOver();
                    return;
                }

                continue;
            }

            if (isOutOfWorldBorders(pickupPosition, pickupHalfSize)) {
                pickups.erase(pickups.begin() + i);
                std::cout << "[DEBUG] Pickup (idx: "<< i <<") removed because is outside of world" << std::endl;
            }
        }

        // Enemies collisions
        for (Enemy* e : enemies) {
            GLfloat * enemyPosition = e->getPosition();

            if (enemyPosition[0] - Enemy::HALF_SIZE[0] < enemyHitbox[0])
                enemyHitbox[0] = enemyPosition[0] - Enemy::HALF_SIZE[0];

            if (enemyPosition[0] + Enemy::HALF_SIZE[0] > enemyHitbox[1])
                enemyHitbox[1] = enemyPosition[0] + Enemy::HALF_SIZE[0];

            if (enemyPosition[1] - Enemy::HALF_SIZE[1] < enemyHitbox[2])
                enemyHitbox[2] = enemyPosition[1] - Enemy::HALF_SIZE[1];

            if (enemyPosition[1] - Enemy::HALF_SIZE[1] > enemyHitbox[3])
                enemyHitbox[3] = enemyPosition[1] + Enemy::HALF_SIZE[1];

            if (collissionBetween(enemyPosition, Enemy::HALF_SIZE,
                                  playerShipPosition, playerShipHalfSize)
            ) { // inimigo max x < player min x
                std::cout << "[DEBUG] Collision between player and enemy" << std::endl;
                triggerGameOver();
                return;
            }
        }

        // Collision with X borders
        if ((!areEnemiesMovingLeft && enemyHitbox[1] + 2 > WORLD_BORDERS[1]) ||
            (areEnemiesMovingLeft && enemyHitbox[0] - 2 < WORLD_BORDERS[0]) ) {
            currEnemyCountDown++;
            areEnemiesMovingLeft = !areEnemiesMovingLeft;
        } else if (enemyHitbox[2] <= WORLD_BORDERS[2]) { // if enemies collide with bottom border
            triggerGameOver();
            return;
        }





        /**
         * MOVEMENTS
         */
        // Bullets movements
        for (Bullet* b : bullets) {
            b->move();
        }

        // Pickups movements
        for (Pickup* p : pickups) {
            p->move();
        }

        // Enemies movements
        GLfloat enemySpeed = currLvlInfo->enemySpeed[0];
        if (currEnemyCountDown == currLvlInfo->enemyHitsToDown) {
            enemyMoveDir = MOVE_DIRS::DOWN;
            enemySpeed = enemySpeed * 2;
            currEnemyCountDown = 0;
        } else {
            enemyMoveDir = areEnemiesMovingLeft ? MOVE_DIRS::LEFT : MOVE_DIRS::RIGHT;
            enemySpeed = currLvlInfo->enemySpeed[0];
        }

        for (Enemy* e : enemies) {
            e->move(enemyMoveDir, enemySpeed);
        }

        // Enemy fire
        if (enemyCanFire && !idxEnemiesThatFire.empty()) {
            enemyCanFire = false;


            GLint idx = rand() % idxEnemiesThatFire.size();
            std::cout << idx << " " << idxEnemiesThatFire.size() << std::endl;

            for (int i = 0; i < idxEnemiesThatFire.size(); i++)
                std::cout << idxEnemiesThatFire.at(i) << " ";
            std::cout << std::endl;

            GLfloat* enemyPosition = enemies.at(idxEnemiesThatFire.at(idx))->getPosition();

            Bullet* b = new Bullet(
                                    enemyPosition[0],
                                    enemyPosition[1] - Enemy::HALF_SIZE[1] - 3,
                                    MOVE_DIRS::DOWN,
                                    false
                                );

            b->setDamage(1);
            b->setSpeed(1.5f);

            bullets.push_back(b);

            glutTimerFunc(2000, enemyFireTimer, 0);
        }


        frameTimerUp = false;
        needsDraw = true;
    }

    if (needsDraw) {
        draw();
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
            if (playerCanRotate) {
                playerShip->rotate(MOVE_DIRS::LEFT);
                needsDraw = true;
                playerCanRotate = false;
                glutTimerFunc(250, playerRotateTimer, 0);
            }
            break;
        case 'E':
        case 'e':
            if (playerCanRotate) {
                playerShip->rotate(MOVE_DIRS::RIGHT);
                needsDraw = true;
                playerCanRotate = false;
                glutTimerFunc(250, playerRotateTimer, 0);
            }
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
            triggerGameOver();
            break;

    }
}

GLvoid gameTimer(GLint value) {
    frameTimerUp = true;

    if (gameState == GAME_STATE::PLAYING)
        glutTimerFunc(16, gameTimer, 0);
}

// On window resize also resizes world screen and keeps original aspect ratio
GLvoid onWindowResize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Base equation R = W / H
    const float NEW_AR = float(w) / float(h);

    if (NEW_AR < INITIAL_AR) { // mais altura que largura
        const int NEW_HEIGHT = w / INITIAL_AR;
        glViewport(0, (h - NEW_HEIGHT) / 2, w, NEW_HEIGHT);
    } else if (NEW_AR > INITIAL_AR) { // mais largura que altura
        const int NEW_WIDTH = h * INITIAL_AR;
        glViewport((w - NEW_WIDTH) / 2, 0, NEW_WIDTH, h);
    } else {
        glViewport(0, 0, w, h);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(nullptr)); // seed random generator

    GLfloat initialHeartsPosition[2] = {
            WORLD_BORDERS[0] + HpHeart::hpHeartSize[0] + 2,
            WORLD_BORDERS[2] + HpHeart::hpHeartSize[1] + 2
                                    };
    GLfloat spaceXHearts = 2;
    for (GLshort i = 0; i < PlayerShip::getMaxHp(); i++) {
        playerHpHeartsUI.push_back(new HpHeart(
                                            initialHeartsPosition[0] + (HpHeart::hpHeartSize[0] + spaceXHearts) * i,
                                            initialHeartsPosition[1])
                                            );
    }

    // Init glut environment
    glutInit(&argc, argv);

    // Define Display Mode
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set window position in the center of screen
    const GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    const GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(screenWidth / 2 - INITIAL_WINDOW_SIZE[0] / 2, screenHeight / 2 - INITIAL_WINDOW_SIZE[1] / 2);

    // Set window size
    glutInitWindowSize(INITIAL_WINDOW_SIZE[0], INITIAL_WINDOW_SIZE[1]);

    // Create window and set title
    glutCreateWindow("Viztui - The Space War");

    setupLevels();
    currLvlInfo = level2;

    //createEnemies();
    //createPlayerShip();

    openMainMenu();

    // Set display callback
    //glutDisplayFunc(draw);

    glutReshapeFunc(onWindowResize);

    // Set keyboard callback
    //glutKeyboardFunc(keyboard);

    // Set idle function
    //glutIdleFunc(idle);

    //glutTimerFunc(16, gameTimer, 0);
    //glutTimerFunc(1000, enemyFireTimer, 0);

    // run main loop
    glutMainLoop();
    return 0;
}