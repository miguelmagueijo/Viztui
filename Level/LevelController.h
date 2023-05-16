//
// Created by Miguel Magueijo on 16/05/2023.
//

#ifndef VIZTUI_LEVELCONTROLLER_H
#define VIZTUI_LEVELCONTROLLER_H

#include "../Viztui.lib.h"
#include "../PlayerShip/PlayerShip.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyBasic.h"
#include "../Bullet/Bullet.h"
#include "../Enemy/EnemyFire.h"
#include "../UiElements/HpHeart.h"
#include "../Enemy/EnemyMiner.h"
#include "../Pickup/PickupMoreHp.h"
#include "../Pickup/PickupMoreDamage.h"
#include "../Pickup/PickupTwoBullets.h"
#include "../Menu/MenuController.h"


// Struct to save level information
typedef struct LevelInfo {
    // Enemies X space to occupy in world (value between 0-1)
    GLfloat xPerToOcupy;
    // Enemies X space between enemies
    GLfloat enemySpaceX;
    // Enemy max hits on border before moving down
    GLint enemyHitsToDown;
    // Enemy speed move speed when moving in X axis and Y axis
    GLfloat enemySpeed[2];
    // Speed to increment each time enemies move down
    GLfloat enemySpeedIncrement[2];
    // Pickup speed when enemy drops it
    GLfloat pickupSpeed;
    // Number of enemy waves in the level and the size of the next 3 vectors
    GLint numWaves;
    // Enemy to be placed in each line, 0 -> basic, 1 -> fire, 2 -> miner
    std::vector<std::vector<GLint>> enemyTypePerLine;
    // Hp of each enemy per wave, 0 -> basic, 1 -> fire, 2 -> miner
    std::vector<std::vector<GLfloat>> enemyHpPerWave;
    // Number of pickups per wave, 0 -> MoreHp, 1 -> TwoBullets, 3 -> MoreDamage
    std::vector<std::vector<GLint>> pickupsPerWave;
    // Pointer to the next level, nullptr and it's the last level
    struct LevelInfo* nextLevel;
} LevelInfo;

namespace LevelController {
    GLvoid hudInit();
    GLvoid start(GLint);
}


#endif //VIZTUI_LEVELCONTROLLER_H
