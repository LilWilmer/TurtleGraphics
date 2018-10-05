#ifndef PEN_H
#define PEN_H

#include "common.h"
/*Tracks current state of the following information*/

typedef struct{
    Coord position; /*Coordinates (x,y)*/
    int angle;      /*Angle from 0°-360°*/
    int fg;         /*Forground colour 0-15*/
    int bg;         /*Background colour 0-7*/
    char pattern;   /*Pattern to be drawn*/
}Pen;

int createPen(Pen **pen);

void freePen(Pen *pen);

#endif