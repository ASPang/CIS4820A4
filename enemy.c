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
int eMode = 0;
int eNum = 1;   //Enemy number

/*Emeny direction*/
char* lrDir = "east";

/* list of players - number of mobs, xyz values and rotation about y */
float playerPosition[MOB_COUNT][4];

/* player controls */
extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

/*Place enemy onto the world*/
void setupEnemy() {
    int i = 0;
    float x=95.5, y, z = 5.5; //Enemy position
    
    /*Determine the y coordinate to place enemy*/
    for (i = 1; i < WORLDY; i++) {
        if (world[(int)floor(x)][i][(int)floor(z)] == 0) {
            y = i;
            break;
        }
    }
    /*Place the enemy at the beginning to be on 5,95*/
    printf("The enemy created is at: %f, %f, %f \n", x, y, z);
    createPlayer(eNum, x, y, z, 0);
    showPlayer(1);
    
    
    /*Set up the enemy direction to be moving right*/
    /*Set up the enemy direction to be moving down*/
}

/*Determine the state of the enemy and perform appropriate actions*/
void enemyMode() {
    /*Determine what mode the enemy is in*/
    if (eMode == 0) { //Search mode
        
    }
    else if (eMode == 1) { //Fight mode
        
    }
}

/*Update enemy in the world*/
void updateEnemy() {
    float xPos, yPos, zPos; //Current enemy Position
    
    /*Get the current position of the enemy*/
    getEnemyPosition(eNum, &xPos, &yPos, &zPos);
    //printf("The enemy created is at: %f, %f, %f \n", xPos, yPos, zPos);
    /*Determine if the enemy can move in that direction*/
    
    
    
    /*Update the enemy position in the game world*/
    moveEnemy();
    
    /*Draw enemy to the screen*/
    setPlayerPosition(eNum, xPos, yPos, zPos, 0);
    //showPlayer(1);
}

void getEnemyPosition(int number, float *x, float *y, float *z) {
    *x = playerPosition[number][0];
    *y = playerPosition[number][1];
    *z = playerPosition[number][2];
}

/*Determine if the enemy can move in that direction*/
int predictEnemyMove() {
    
}

/*Update enemy position*/
void moveEnemy() {
    
    
    /*Move the enemy based on the direction*/
    
}



/*Search algorithm*/
