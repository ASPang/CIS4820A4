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
    float ySpot;
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
    //float x=95.5, y, z = 5.5; //Enemy position
    float x= 75, y, z = 45; //TESTING!!!!!!!!!!
    
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
    enemy.zSpot = 0.0;
    enemy.ySpot = 0.0;
    
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
    //getEnemyPosition(enemy.id, &xPos, &yPos, &zPos);
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
    int tempX, tempY, tempZ; 
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &x, &y, &z);
    
    /*Determine if the enemy hits a cube*/
    tempX = (int)floor(x + enemy.dx*2);   //x-direction and buffer space
    tempZ = (int)floor(z + enemy.dz*2);   //z-direction and buffer space
    tempY = (int)floor(y); 
    printf("Enemy current position is at: %f, %f, %f \n", x,y,z);
    if (world[tempX][tempY][tempZ] != 0 && enemy.ySpot <= 0.0) {
      printf("ENEMY HAS HIT A CUBE \n");
      /*Determine if enemy can climb the cube*/
      if (tempY + 1 < WORLDY) {  //Determine if enemy can climb 1 squares
         if (world[tempX][tempY + 1][tempZ] == 0) {  //Climb one cube
            /*enemy.dy = 0.1;
            enemy.ySpot = 1.0;*/
            printf("---climbed 1 \n");
            setPlayerPosition(enemy.id, x + (enemy.dx*3), y + 1, z + (enemy.dz*3),0);
         }
         else {
            printf("---Cannot climb 1\n");
         }
      }
      else if (tempY + 2 < WORLDY) {   //Determine if enemy can climb 2 squares
         if(world[tempX][tempY + 2][tempZ] == 0) {   //Attempt to climb two cubes
            /*enemy.dy = 0.1;
            enemy.ySpot = 2.0;*/
            printf("---climbed 2 \n");
            setPlayerPosition(enemy.id, x + (enemy.dx*3), y + 2, z  + (enemy.dx*3),0);
         }
         else {
            printf("---Cannot climb 2\n");
         }
      }         
      else {   //Cannot climb and would need to find a new way out
         printf("---Cannot climb at all going to determine a brand new path\n");
         /*Determine another path*/
         searchEPath();
      }
    }
    
    /*Determine if there's a cube under the player*/
    if (tempY > 0) {
       /*Determine if there's a cube below the enemy*/
       if ((world[tempX][tempY - 1][tempZ] == 0) && (enemy.ySpot <= 0.0)) {
         //printf("There's no cube under enemy \n");
         enemy.dy = -0.1;
       }
    }
    
    if (enemy.ySpot > 0.0) {  //NOT NECESSARY AS THE ENEMY NOW TELE TO THE NEXT BLOCK
       //enemy.ySpot = enemy.ySpot - 0.1;
    }
    
    /*Convert the direction to an integer*/
    xPos = (int)floor(x);
    zPos = (int)floor(z);
    
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
    //printf("---after direction = %f, %f \n", enemy.dx, enemy.dz);
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
    //printf("---old enemy position = %f, %f, %f \n", xPos, yPos, zPos);
    xPos = xPos + enemy.dx;
    zPos = zPos + enemy.dz;
    
    /*Move the enemy based on the direction*/
    setPlayerPosition(enemy.id, xPos, yPos, zPos, 0);
    
    //printf("New enemy direction = %f, %f \n", enemy.dx, enemy.dz);
    //printf("---New enemy position = %f, %f, %f \n", xPos, yPos, zPos);
}

/*Determine another route*/
void searchEPath() {
   /*Determine possible openings*/
   if (enemy.dx < 0) {  //moving South
   }
   else if (enemy.dx < 0) {  //moving North
   }
   else if (enemy.dz > 0) {  //moving East
   }
   else if (enemy.dz < 0) {  //moving West
   }   
}

/*Determine which way to look for clearing*/
void dirSouth() {
    int found = 0; //Determine if a path has been found
    float x, y, z;
    int xPos, yPos, zPos; //Current enemy Position 
    
    /*Get the current position of the enemy*/
    getEnemyPosition(enemy.id, &x, &y, &z);
    
    /*Determine if the enemy hits a cube*/
    xPos = (int)floor(x);   
    yPos = (int)floor(y); 
    zPos = (int)floor(z);       
    
   if (enemy.zTarget == 1) {  //If enemy is to be heading east
      //Check East
      if (enemy.zTarget > 0) {
         found = lookEast(xPos, yPos, zPos);
         
         if (found == 0) {
            found = lookEast(xPos, yPos + 1, zPos);
         }
         
         if (found == 0) {
            found = lookEast(xPos, yPos + 2, zPos);
         }
      }
      else {
      }
      
      //Check West
   }
   else {   //If enemy is to be heading east
      //Check East
      //Check West
   }
   
   if (found == 0) { //Check North
   }
}


/*Enemy Look East for a clearing
 *0 = false (no the path is blocked)
 *1 = true (there is a clearing)
 */
int lookEast(int x, int y, int z) {
   z = z + 1;  //Look ahead
   
   if (z > -1 && z < WORLDY) {
      if (world[x][y][z] == 0) {
         enemy.dz = 0.1;   //Head east direction
         enemy.dx = 0;
         
         return 1;
      }
   }
   
   return 0;   //No new path possible
}

/*Enemy Look West for a clearing
 *0 = false (no the path is blocked)
 *1 = true (there is a clearing)
 */
int lookWest(int x, int y, int z) {
   z = z - 1;  //Look ahead
   
   if (z > -1 && z < WORLDY) {
      if (world[x][y][z] == 0) {
         enemy.dz = 0.1;   //Head east direction
         enemy.dx = 0;
         
         return 1;
      }
   }
   
   return 0;   //No new path possible
}

/*Enemy Look North for a clearing
 *0 = false (no the path is blocked)
 *1 = true (there is a clearing)
 */
int lookNorth(int x, int y, int z) {
   x = x + 1;  //Look ahead
   
   if (x > -1 && x < WORLDX) {
      if (world[x][y][z] == 0) {
         enemy.dz = 0;   //Head east direction
         enemy.dx = 0.1;
         
         return 1;
      }
   }
   
   return 0;   //No new path possible
}

/*Enemy Look South for a clearing
 *0 = false (no the path is blocked)
 *1 = true (there is a clearing)
 */
int lookSouth(int x, int y, int z) {
   x = x - 1;  //Look ahead
   
   if (x > -1 && x < WORLDX) {
      if (world[x][y][z] == 0) {
         enemy.dz = 0;   //Head east direction
         enemy.dx = -0.1;
         
         return 1;
      }
   }
   
   return 0;   //No new path possible
}

/*Search algorithm*/
