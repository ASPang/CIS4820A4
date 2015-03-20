
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

/*Library used starting from Assignement 1-2*/
#include <time.h>

/*Library used for Assignment 3*/
/* From Beginning Linux Programming, 4th edition, byt Matthew and Stone. */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

        /* world size and storage array */
#define WORLDX 100
#define WORLDY 50
#define WORLDZ 100
GLubyte  world[WORLDX][WORLDY][WORLDZ];

#define MAX_DISPLAY_LIST 500000

/*Functions for CIS4820 Assignment 1*/
int climbCube(int, int, int);
void gameWall();

void gravity();
void avoidCubeEdge();

void landscape();
void grassLand();
void waterFlow();
void mountainTops();
void perlinNoise();
void fillMountain(int, int, int);

void cloudFloat();
void cloudShape();
void createCloud(int, int, int, int *, int);
void moveCloud();
void updateCloudLoc();


/*Functions for CIS4820 Assignment 2*/
void worldOrientation();
void moveProjectile();
void initProjectiles();
void updateProjectiles();
void objectCollision();
void clearProjectile(int);
void nextProjLoc(float *, float *, float, float, int );
float nextProjHeight(float , float, float *);

float calSpeed(int, int);
float calAngle(int, int);


/*Functions for CIS4820 Assignment 3 - Networking*/
void openSocketServer();
void openSocketClient();
void writeSocket();

void sendViewPos();
void sendViewOrient();
void sendProjectile(char *, char *);
void sendAngleInfo(char *, char *);

void convertPosNumDigit(char *);
void convertOrientNumDigit(char *);

void readSocket();
void parseViewPos(char *);
void parseOrientPos(char *);
void parseProjectInfo(char *);
void parseAngleInfo(char *);

void createClientProj(float , float );
void convertProjNumDigit(char *);

void setBarrelView();

char ** splitNumMsgInfo(char *, int, int);

//2D Drawing Functions
void drawMapArea(int, int, int, int, int);
void drawPlayerToMap(int, int, int);
void drawProjToMap(int, int, int);

void drawCordToMap(int, int, int );
void convertPosForMap(char *);

void drawMapCord(int, int, int, int);
void addCordToMap(int, int, char *, int);

//Thread Functions
void *clientThread(void *);


/*Functions for CIS4820 Assignment 4 - Enemy Opponent*/
//void updateEnemy();
void setupEnemy();
void moveEnemy();

void getEnemyPosition(int, float*, float*, float*);

void enemyEastWestDir();
void searchEPath();
void dirSouthAndNorth();
void dirEastAndWest();

void enemyFireProj(float, float, float, float, float);
int directHit(float, int, int, int);
int hitResult(float, float, float, int, int, int);
int indirectHit(int, int, int, int);
