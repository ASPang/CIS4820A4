#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

#define MOB_COUNT 10

/* Enemy State:
 * 0 = search mode
 * 1 = fight mode
 */
//int eMode = 0;
//int eNum = 1;   //Enemy number

struct enemyStruct {
    float dx;
    float dy;
    float dz;
    float zSpot;
    int zTarget;
    int xTarget;
    int mode;
    int id;
};

struct enemyStruct enemy;

/*Emeny direction*/
char* lrDir = "east";

/* list of players - number of mobs, xyz values and rotation about y */
extern float playerPosition[MOB_COUNT][4];

/* player controls */
extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

/*Place enemy onto the world*/
void setupEnemy() {
    int i = 0;
    float x=95.5, y, z = 5.5; //Enemy position
    
    /*Set up the variable for the struct*/
    enemy.id = 1;
    enemy.mode = 0;
    
    /*Determine the y coordinate to place enemy*/
    for (i = 1; i < WORLDY; i++) {
        if (world[(int)floor(x)][i][(int)floor(z)] == 0) {
            y = i;
            break;
        }
    }
    /*Place the enemy at the beginning to be on 5,95*/
    printf("The enemy created is at: %f, %f, %f \n", x, y, z);
    createPlayer(enemy.id, x, y, z, 0);
    showPlayer(1);
        
    /*Set up the enemy direction*/
    enemy.dy = 0.0;   //Not going to moved up or down
    enemy.dz = 0.0;   //Move right (east)
    enemy.dx = -0.1;  //Move down (south)
    enemy.zTarget = 1;   //Move right (east)
    enemy.xTarget = -1;  //Move down (south)
    enemy.zSpot = 0;
    
}

/*Determine the state of the enemy and perform appropriate actions*/
void enemyMode() {
    /*Determine what mode the enemy is in*/
    if (enemy.mode == 0) { //Search mode
        
    }
    else if (enemy.mode == 1) { //Fight mode
        
    }
}

/*Update enemy in the world*/
void updateEnemy() {
    float xPos, yPos, zPos; //Current enemy Position
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &xPos, &yPos, &zPos);
    //printf("The enemy created is at: %f, %f, %f \n", xPos, yPos, zPos);
    /*Determine if the enemy can move in that direction*/
    predictEnemyMove();
    
    
    /*Update the enemy position in the game world*/
    moveEnemy();
    
    /*Draw enemy to the screen*/
    //setPlayerPosition(enemy.id, xPos, yPos, zPos, 0);
    //showPlayer(1);
}


/*Get the enemy's current position in the game*/
void getEnemyPosition(int number, float *x, float *y, float *z) {
    *x = playerPosition[number][0];
    *y = playerPosition[number][1];
    *z = playerPosition[number][2];
}

/*Determine if the enemy can move in that direction*/
int predictEnemyMove() {
    float x, y, z;
    int xPos, yPos, zPos; //Current enemy Position
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &x, &y, &z);
    
    xPos = (int)floor(x);
    zPos = (int)floor(z);
    
    /*Determine if the enemy needs to change direction
    if (zPos >= 95 && enemy.dz == -1) { //Enemy can is planned to move west
        enemy.zTarget = 1;   //Update enemy position to move east
    }
    else if (zPos <= 5 && enemy.dz == 1) { //Enemy can is planned to move east
        enemy.dz = -1;   //Update enemy position to move west
    }*/
    
    /*Determine if the enemy needs to change direction
    if (zPos >= 95 && enemy.zTarget == -1) { //Enemy can is planned to move west
        enemy.dz = 1;   //Update enemy position to move east
    }
    else if (zPos <= 5 && enemy.zTarget == 1) { //Enemy can is planned to move east
        enemy.zTarget = -1;   //Update enemy position to move west
    }*/
    printf("before direction = %f, %f \n", enemy.dx, enemy.dz);
    /*Determine mob direction*/
    if (enemy.dx != 0) {//Mob is going south or north
        enemy.dz = 0;
        
        /*Determine if the mob can move to that block*/
        if (xPos < 5 || xPos > 95) {
            enemy.dx = 0;
            enemy.zSpot = 5.5;
            
            /*Determine the east or west direction it should go in*/
            if(enemy.zTarget == 1) { //Enemy should move east
                enemy.dz = 0.1;
            }
            else if (enemy.zTarget == -1) { //Enemy should move west
                enemy.dz = -0.1;
            }
        }
        
    }
    else {  //Enemy is heading east or west        
        /*Determine if the mob can move to that block*/
        if (enemy.zSpot <= 0) {
            enemy.dz = 0;
            enemyEastWestDir();
            
            /*Determine if the player should move up or down*/
            if (xPos <= 50) { //Move North
                enemy.dx = 0.1;
            }
            else { //Move South
                enemy.dx = -0.1;
            }
        }
        else {
            enemy.zSpot -= 0.1;
        }
    }
    printf("---after direction = %f, %f \n", enemy.dx, enemy.dz);
}

void enemyEastWestDir() {
    float xPos, yPos, zPos; //Current enemy Position
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &xPos, &yPos, &zPos);
    
    /*Determine if the enemy needs to change direction*/
    if (zPos >= 95 && enemy.zTarget == -1) { //Enemy can is planned to move west
        enemy.zTarget = 1;   //Update enemy position to move east
    }
    else if (zPos <= 5 && enemy.zTarget == 1) { //Enemy can is planned to move east
        enemy.zTarget = -1;   //Update enemy position to move west
    }
}

/*Update enemy position*/
void moveEnemy() {
    float xPos, yPos, zPos; //Current enemy Position
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &xPos, &yPos, &zPos);
    printf("---old enemy position = %f, %f, %f \n", xPos, yPos, zPos);
    xPos = xPos + enemy.dx;
    zPos = zPos + enemy.dz;
    
    /*Move the enemy based on the direction*/
    setPlayerPosition(enemy.id, xPos, yPos, zPos, 0);
    
    //printf("New enemy direction = %f, %f \n", enemy.dx, enemy.dz);
    printf("---New enemy position = %f, %f, %f \n", xPos, yPos, zPos);
}



/*Search algorithm*/
