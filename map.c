#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

/*Screen Messages*/
extern int msgHitDirect;
extern int msgHitInDirect;

/*Network Server Client*/
extern int netClient;

	/* 2D drawing functions */
extern void  draw2Dline(int, int, int, int, int);
extern void  draw2Dbox(int, int, int, int);
extern void  draw2Dtriangle(int, int, int, int, int, int);
extern void  set2Dcolour(float []);

   /* projectile Information */
extern float projectile[10][12];  //dx, dy, velocity
extern float projNumber;

   /*Projectile Calculation Function*/
extern void nextProjLoc(float *, float *, float, float, int );
extern float nextProjHeight(float , float, float *);

	/* viewpoint control */
extern void getViewPosition(float *, float *, float *);

	/* size of the window in pixels */
extern int screenWidth, screenHeight;

/*Draws the map area and its boarder*/
void drawMapArea(int mX1, int mY1, int mX2, int mY2, int mSize) {
   int lineWidth = 5;   //Map boarder width
   float mapBuf = 0.01;
   
   /*Colour Variables*/
   GLfloat black[] = {0.0, 0.0, 0.0, 0.8};
   GLfloat grey[] = {0.0, 0.0, 0.0, 0.5};
   
   /*Modify map with padding*/
   mX1 -= screenWidth * mapBuf;
   mX2 += screenWidth * mapBuf;
   
   mY1 += screenHeight * mapBuf;
   mY2 -= screenHeight * mapBuf;
   
   /*Display Map coordinates*/
   drawMapCord(mX1, mY1, mX2, mY2);
   
   /*Draw lines to indicate the boundary of the map*/
   set2Dcolour(black);
   //draw2Dline(int x1, int y1, int x2, int y2, int lineWidth)
   draw2Dline(mX1 - lineWidth + 1, mY1, mX1 + (mX2 - mX1 + lineWidth), mY1, lineWidth);   //Top boarder
   draw2Dline(mX1 - lineWidth + 1, mY2, mX1 + (mX2 - mX1 + lineWidth), mY2, lineWidth);   //Bottom boarder
   
   draw2Dline(mX1 - lineWidth/2, mY1, mX1 - lineWidth/2, mY1 + (mY2 - mY1), lineWidth);   //Left boarder
   draw2Dline(mX2 + (lineWidth/2), mY1, mX2 + (lineWidth/2), mY1 + (mY2 - mY1), lineWidth);   //Right boarder
   
   /*Draw the map area**/
   set2Dcolour(grey);
   draw2Dbox(mX1, mY1, mX2, mY2); //draw2Dbox(int x1, int y1, int x2, int y2) 
}

/*Draw the player to the map*/
void drawPlayerToMap(int mX, int mY, int mSize) {
   /*Player Variables*/
   int pSize = screenWidth * 0.01; //Player size
   float x, y, z;
   int pX, pY;
   
   /*Colour Variable*/
   GLfloat green[] = {0.0, 0.5, 0.0, 0.5};
    
   /*Get player's current position*/
   getViewPosition(&x, &y, &z);
    //printf("Player - x, y, z - %f, %f, %f \n", x, y, z);
   /*Convert the location to positive integer by:
    *1)Convert cord to a percentage
    *2)Multiple it by map size
    *3)convert it to a positive number
    */
   pX = (int)floor(z/100 * mSize) * -1;
   pY = (int)floor(x/100 * mSize) * -1;
    
   /*Convert location to map*/
   mX += pX;
   mY += pY;
    
   /*Display player's current location on the map*/
   drawCordToMap(mX, mY, pSize);
    
   /*Create a 20x20 pixel square and center it to represent the player*/
   set2Dcolour(green);
   draw2Dbox(mX - pSize, mY - pSize, mX + pSize, mY + pSize); //int x1, int y1, int x2, int y2
}

/*Display Enemy's current position*/
void drawEnemyToMap(int mX, int mY, int mSize) {
    /*Player Variables*/
    int pSize = screenWidth * 0.01; //Player size
    float x, y, z;
    int pX, pY;
    
    /*Colour Variable*/
    GLfloat red[] = {0.5, 0.0, 0.0, 0.5};
    
    /*Get player's current position*/
    getEnemyPosition(1,&x, &y, &z);
    //printf("Player - x, y, z - %f, %f, %f \n", x, y, z);
    /*Convert the location to positive integer by:
     *1)Convert cord to a percentage
     *2)Multiple it by map size
     *3)convert it to a positive number
     */
    pX = (int)floor(z/100 * mSize);
    pY = (int)floor(x/100 * mSize);
    
    /*Convert location to map*/
    mX += pX;
    mY += pY;
        
    /*Create a 20x20 pixel square and center it to represent the player*/
    set2Dcolour(red);
    draw2Dbox(mX - pSize, mY - pSize, mX + pSize, mY + pSize); //int x1, int y1, int x2, int y2
}

/*Draw any projectiles to the map*/
void drawProjToMap(int mX, int mY, int mSize) {
   /*Player Variables*/
   int pSize = screenWidth * 0.005; //projectile size
   float x, y, z;
   int pX, pY;
   int newX, newY;
   int i;   //Loop counters
   
   /*Colour Variable*/
   GLfloat blue[] = {0.0, 0.0, 0.5, 0.8};
      
   /*Go through all the projectiles*/   
   for (i = 0; i < 10; i++) {      
      /*Get current projectile position*/
      x = projectile[i][0];
      z = projectile[i][2];
       
      if (x >= 0) {
         /*Convert the location to positive integer by:
          *1)Convert cord to a percentage
          *2)Multiple it by map size
          *3)convert it to a positive number
          */
         pX = (int)floor(z/100 * mSize);
         pY = (int)floor(x/100 * mSize);
         
         /*Convert location to map*/
         newX = mX + pX;
         newY = mY + pY;
         
         /*Draw a square and center it to represent the projectile*/
         set2Dcolour(blue);
         draw2Dbox(newX - pSize, newY - pSize, newX + pSize, newY + pSize); //int x1, int y1, int x2, int y2
      }            
   }
}

/*Display the Player's current position*/
void drawCordToMap(int mX, int mY, int pSize) {
   float x, y, z;
   int cordLen = 6;
   int strLen = 20;
   int i = 0;  //Loop counter 
   char strX[cordLen], strY[cordLen], strZ[cordLen], cordStr[strLen];
   
   /*Set the text colour*/
   GLfloat black[] = {0.0, 0.0, 0.0, 0.9};
   set2Dcolour(black);
   
   /*Get player's current position*/
   getViewPosition(&x, &y, &z);
   
   /*Convert to a positive number*/
   x = x * -1;
   y = y * -1;
   z = z * -1;
    
   /*Convert coordinates to a string*/
   sprintf(strX, "%f", x);    
   sprintf(strY, "%f", y);    
   sprintf(strZ, "%f", z);
    
   /*Trimming the decimal place down to two*/
   strX[5] = '\0';
   strY[5] = '\0';
   strZ[5] = '\0';
    
   fflush(stdout);
    
   /*Convert the three values into two digit string numbers - example 2 = "02" */
   convertPosForMap(strX);
   convertPosForMap(strY);
   convertPosForMap(strZ);
        
   /*Concate the message*/
   strcpy(cordStr,"("); //Set up message
   strcat(cordStr, strX);
   strcat(cordStr, ",");
   strcat(cordStr, strY);
   strcat(cordStr, ",");
   strcat(cordStr, strZ);
   strcat(cordStr, ")\0");

   /*Set text position*/
   glRasterPos2i(mX - pSize * 3, mY - pSize * 2); 
   
   /*Display text to screen*/
   for (i = 0; i < strLen; i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, cordStr[i]); 
   }
    
}

/*Convert the three values into two digit string numbers - example 2 = "02" */
void convertPosForMap(char * str) {
    int strLen = 6;
    int i = 0;  //Loop counter
    char newStr[strLen];
    
    /*Look at the 3 character (position 2) of the string. Determine if it's a decimal*/
    if (str[2] != '.') {
        /*Add zero at the front*/
        for (i = 0; i < strLen; i++) {
            if (i == 0) {
                newStr[i] = '0';
            }
            else {
                newStr[i] = str[i-1];
            }
        }
        
        /*Replace old string with the new one*/
        strcpy(str, newStr);
    }
}

/*Draw the map coordinate*/
void drawMapCord(int mX1, int mY1, int mX2, int mY2) {
   int font = 4;
   
   addCordToMap(mX1, mY1 - 9, "(0,99)", 6);
   addCordToMap(mX1, mY2 + 5, "(0,0)", 5);
   addCordToMap(mX2 - font * 8, mY1 - 9, "(99,99)", 7);
   addCordToMap(mX2 - font * 7, mY2 + 5, "(0,99)", 6);
}

void addCordToMap(int mX, int mY, char *str, int strLen) {   
   int i = 0;  //Loop counter
   
   /*Set the text colour*/
   GLfloat red[] = {0.5, 0.0, 0.0, 0.9};
   set2Dcolour(red);
   
   /*Set text position*/
   glRasterPos2i(mX, mY); 
   
   /*Display text to screen*/
   for (i = 0; i < strLen; i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, str[i]); 
   }
}


/*Draw Message to Screen about Hits*/
void showHitMessage(int strLen, char * str) {
    int x = 450, y = 300;   //Message screen location
    int i;
    /*Set the text colour*/
    GLfloat red[] = {0.5, 0.0, 0.0, 0.9};
    set2Dcolour(red);
    
    /*Set text position*/
    glRasterPos2i(x, y);
    
    /*Display text to screen*/
    for (i = 0; i < strLen; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}


/*Counts down to when the AI can shoot again*/
int pauseMsgOnScreen() {
    static clock_t updateStart;
    clock_t updateEnd;
    static int resetTime = 1;
    int milsec = 10000; //Milliseconds;
    double diff;
    
    struct timeval  tv;
    double time_in_mill;
    
    gettimeofday(&tv, NULL);
    /*Determine if the timer has been set*/
    if (resetTime == 1) {
        /*Reset the timer*/
        resetTime = 0;
        
        time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
        
        updateStart = time_in_mill;
        
    }
    else if (resetTime == 0) {
        /*Determine if 0.08 second has passed*/
        time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond
        
        updateEnd = time_in_mill;
        diff = ((updateEnd - updateStart));
        
        if (diff >= 5000) {
            resetTime = 1;  //Reset the timer
            msgHitDirect = 0;
            msgHitInDirect = 0;
            return 1;
        }
    }
    
    return 0;   //Don't update the function
}
