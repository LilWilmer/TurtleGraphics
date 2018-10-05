/*****************************************************************************
* AUTH: William Payne
* FILE: pen.h
* LAST MOD: 05/10/2018
* PURPOSE: Header file for pen.c
*****************************************************************************/
/*HEADER GUARD--------------------------------------------------------------*/
#ifndef PEN_H
#define PEN_H

/*INCLUDE STATEMENTS--------------------------------------------------------*/
#include "common.h"

/*typedef enum FG{
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    magenta = 5,
    cyan = 6,
    grey = 7
}FG;

typedef enum BG{
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    L_GREY = 7,
    D_GREY = 8,
    L_RED = 9,
    L_GREEN = 10,
    L_YELLOW = 11,
    L_BLUE = 12,
    L_MAGENTA = 13,
    L_CYAN = 14,
    WHITE = 15
}BG;*/

/*Tracks current state of the following information*/
/*----------------------------------------------------------------------------
* Pen struct:
* ---   ---   ---   ---
* Tag: --
* Typedef: Pen
* Purpose: Tracks information pertaining to GCommand functions and line() in
*          effects.c.
* FIELDS:
*   position(Coord) ~ Coordinate of the cursor [x,y]
*   angle(double)   ~ Angle from 0.0f°-360.0f°
*   fg(int)         ~ Forground colour 0-15
*   bg(int)         ~ Background colour 0-7
*   pattern(char)   ~ Pattern to be drawn
* ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---
*/
typedef struct{
    Coord position; /*Coordinates (x,y)*/
    double angle;      /*Angle from 0.0f°-360.0f°*/
    int fg;         /*Forground colour 0-7*/
    int bg;         /*Background colour 0-15*/
    char pattern;   /*Pattern to be drawn*/
}Pen;


int createPen(Pen **pen);

void freePen(Pen *pen);

#endif