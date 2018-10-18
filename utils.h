/*****************************************************************************
* AUTH: William Payne
* FILE: utils.h
* LAST MOD: 08/10/2018
* PURPOSE: Header file for utils.c
*****************************************************************************/
/*START FILE*/
#ifndef MYUTILS_H
#define MYUTILS_H

#include<math.h>
#include"common.h"

/*CONSTANTS-----------------------------------------------------------------*/
#define FALSE 0
#define TRUE !FALSE
#define PI 3.14159265358979323846

/*MACROS--------------------------------------------------------------------*/
#define CAPITALIZE(a) ((a)-32)
#define LOWERCASE(a) ((a)+32)
#define E(x) printf("line:%d\n",x);fflush(stdout);
#define CLEAR_SCREEN printf("\033[H\033[2J")
#define NEW_COORD {{0.0f, 0.0f}}

/*TYPEDEFS AND STRUCTS------------------------------------------------------*/
/*VOID FUNCTION POINTER*/
/**
* VoidFunc function pointer:
* --- --- --- ---
* Used when type casting a function pointer to an unknown type.
*/
typedef void (*VoidFunc)(void);

/*Coordinate struct*/
/*----------------------------------------------------------------------------
* Coordinate struct:
* ---   ---   ---   ---
* Tag: --
* Typedef: Coord
* Purpose: Holds a x and y coordinate.
* FIELDS: pos(int[2])   ~ x and y coordinate.
*   --
* ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---
*/
typedef struct{
    double pos[2];
}Coord;

/*FORWARD DECLARTIONS-------------------------------------------------------*/

/**
* captialize():
* --- --- --- ---
* Capitalizes all the alphabetic characters in a string.
*/
void capitalize( char *text);

/*MATH FUNCTIONS*/
/**
* rounds():
* --- --- --- ---
* Rounds a double value to the nearest whole number and returns the result
* as an integer.
*/
int rounds(double num);

/**
* degreesToRadians():
* --- --- --- ---
* Converts the value at angle from degrees to radians
*/
void degreesToRadians( double *angle);

/**
* calculatePosition():
* --- --- --- ---
* Calculates a new coordinate position given an origin, angle and a distance.
*/
void calculatePosition( Coord *newPos, Coord *currPos
                      , double distance, double angle);

/**
* realign():
* --- --- --- ---
* Takes in two coordinates, determines if the roundedPos is out of alignment
* and if so is set to the realPos coordinate.
*/
void realign(Coord *realPos, Coord *roundedPos);

/**
* nextLine:
* --- --- --- ---
* Function has a static counter and points the cursor to line at count
* incrementing count on each function call.
*/
void nextLine(void);

/**
 * Resets terminal colours to default.
 */
void setColourDefault(void);
#endif
/*END FILE*/

