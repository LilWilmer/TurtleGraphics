/*****************************************************************************
* AUTH: William Payne
* FILE: Utils.c
* LAST MODE: 05/10/2018
* Purpose: General Utilities
*****************************************************************************/
#include "utils.h"
static const double TOL = 0.3f; /*Tolerance used in Coordinate precision*/

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
        if( temp >= 'a' && temp <= 'z')
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
void degreesToRadians( double *angle)
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
    degreesToRadians(&angle);
    newPos->pos[0] = currPos->pos[0] + distance * cos(angle);
    newPos->pos[1] = currPos->pos[1] + distance * sin(angle);
}

/*****************************************************************************
* FUNCTION: realign()
*-----------------------------------------------------------------------------
* IMPORTS: 
*   realPos(Coord)      ~ The real position a coordinate should be in.
*   currPos(Coord)   ~ A less accurate coordinate being realigned.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Checks to see whether the imported rounded corrdinate is further enough
*   out of its alignment with its real position to justify resetting it.
*
* NOTES: 
*   In regards to the line function the current tollerance is set to 0.3, it
*   seems to work for all test cases in the range of 0.3-0.999 anything lower
*   or higher results in inaccurate plots.
*****************************************************************************/
void realign(Coord *realPos, Coord *currPos)
{
    if(realPos->pos[0] - currPos->pos[0] <= -TOL || realPos->pos[0] - currPos->pos[0] >= TOL)
    {
        currPos->pos[0] = realPos->pos[0];
    }
    if(realPos->pos[1] - currPos->pos[1] <= -TOL || realPos->pos[1] - currPos->pos[1] >= TOL)
    {
        currPos->pos[1] = realPos->pos[1];
    }
}

/**
* nextLine():
* --- --- --- ---
* Function has a static counter and points the cursor to line at count
* incrementing count on each function call.
*/
void nextLine(void)
{
    static int ii = 0;
    ii++;
    printf("\033[%d;1H",ii);
}

/**
 * Changes the terminal colours back to default.
 */
void setColourDefault(void)
{
    printf("\033[0m");
}
