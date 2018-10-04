/********************************************************************
* Author: William Payne
* File Name: Utils.c
* Date Last Modified: 23\9\2018
* Purpose: General Utilities
********************************************************************/
#include "utils.h"
/**********************************************************
* Function: capitalize
*  Imports: array(int*), length(int)
*  Exports: none
*  Purpose: Capitalize all letters in a string
**********************************************************/
void capitalize( char *text)
{
    int ii;
    char temp;

    ii = 0;
    do
    {
        temp = *(text + ii);

        /*97 - 122 are ascii values for lowercase letters*/
        if( temp > 96 && temp < 123)
        {
            *( text + ii) = CAPITALIZE(temp);
        }
        ii++;
    }
    while( '\0' != *( text + ii));
}

/*****************************************************************************
* FUNCTION: round
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'num'    ~ A double value for rounding.
*
*  EXPORTS: 
*  'rounded'    ~ The rounded double value returned as an int.
*
*  PURPOSE: 
*  Rounds a double value using ceil and floor and returns the value.
*
*  NOTES:
*  Round down if < 0.5
*****************************************************************************/
int rounds(double num)
{
    int rounded = 0;

    if((num - (int)num) < 0.5)
    {
        rounded = floor(num);
    }
    else
    {
        rounded = ceil(num);
    }
    return rounded;
}

/*****************************************************************************
* FUNCTION: convertToRadians
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'angle'  ~Double pointer containing the value of angle in degrees
*
*  EXPORTS: 
*  'none'
*
*  PURPOSE: 
*  Converts the degree value at angle to radians.
*****************************************************************************/
void convertToRadians( double *angle)
{
    *angle *= (PI / 180);
}

/*****************************************************************************
* FUNCTION: calculatePosition
*-----------------------------------------------------------------------------
* IMPORTS: 
* 'newPos'      ~double pointer the the new position of the cursor.
* 'currPos'     ~double pointer to the current position of the cursor.
* 'distance'    ~double containing the distance to move the cursor.
* 'angle'       ~double containing the angle to move the cursor on.
*
* EXPORTS: 
* none
*
* PURPOSE: 
* Calculates a coordinate given a starting positon, an angle and a distance.
*
* ERROR CODES: 
* --
*
* NOTES: 
* --
*****************************************************************************/
void calculatePosition( double *newPos, double *currPos
                      , double distance, double angle)
{
    convertToRadians(&angle);
    newPos[0] = currPos[0] + distance * cos(angle);
    newPos[1] = currPos[1] + distance * sin(angle);
}
