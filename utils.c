/********************************************************************
* AUTH: William Payne
* FILE: Utils.c
* LAST MODE: 05/10/2018
* Purpose: General Utilities
********************************************************************/
#include "utils.h"

/*****************************************************************************
* FUNCTION: capitalize
*-----------------------------------------------------------------------------
* IMPORTS: 
*   text(int*)  ~ String to be capitalized.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Captialize all alphabetic characters in the string 'text';
*
* NOTES: 
*   --
*****************************************************************************/
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
* IMPORTS: 
*   num(dobule)     ~ The value to be rounded.
*
* EXPORTS: 
*   rounded(int)    ~ The rounded double value returned as an int.
*
* PURPOSE: 
*   Rounds a double value using ceil and floor and returns the value.
*
* NOTES:
*   Round down if < 0.5
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
* IMPORTS: 
*   angle(double*)  ~ Pointer to an angle in degrees.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Converts the degree value at angle to radians.
*****************************************************************************/
void convertToRadians( double *angle)
{
    *angle *= (PI / 180);
}

/*****************************************************************************
* FUNCTION: calculatePosition
*-----------------------------------------------------------------------------
* IMPORTS: 
*   newPos(Coord)      ~ New position of the cursor.
*   currPos(Coord)     ~ Current position of the cursor.
*   distance(double)   ~ Distance to move the cursor.
*   angle(double)      ~ Angle to move the cursor on.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Calculates a coordinate given a starting positon, an angle and a distance.
*
* ERROR CODES: 
*   --
*
* NOTES: 
*   --
*****************************************************************************/
void calculatePosition( Coord *newPos, Coord *currPos 
                      , double distance, double angle)
{
    convertToRadians(&angle);
    newPos->pos[0] = currPos->pos[0] + distance * cos(angle);
    newPos->pos[1] = currPos->pos[1] + distance * sin(angle);
}
