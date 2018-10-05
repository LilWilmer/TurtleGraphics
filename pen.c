/******************************************************************************
* AUTH: William Payne
* FILE: pen.c
* LAST MOD: 05/10/18
* PURPOSE: File contains functions pertaining to the Pen struct.
******************************************************************************/
#include "pen.h"

/*****************************************************************************
* FUNCTION: createPen
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen**)  ~ Pointer to the new pen pointer
*
* EXPORTS: 
*   '1' ~ Place holder for error code ('1' meaning success).
*
* PURPOSE: 
*   Creates a new Pen struct on the heap and initializes all its fields.
*
* ERROR CODES: 
*   1 ~ No errors.
*
* NOTES: 
*   Pen must be freed before ending program
*****************************************************************************/
int createPen(Pen **pen)
{
    *pen = (Pen*)malloc(sizeof(Pen));

    (*pen)->position.pos[0] = 0.0f;
    (*pen)->position.pos[1] = 0.0f;
    (*pen)->angle = 0.0f;
    (*pen)->fg = 0;
    (*pen)->bg = 1;
    (*pen)->pattern = '#';

    return 1;
}

/*****************************************************************************
* FUNCTION: freePen
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)  ~ Pen struct to be freed.
*
* EXPORTS: none 
*
* PURPOSE: 
*   Frees all heap data associated with the Pen struct.
*
* NOTES: 
*   Simple function but takes away any doubt when freeing, the abstaction
*   allows for easier maintenance of the code as well e.g. freeing struct
*   fields etc..
*****************************************************************************/
void freePen(Pen *pen)
{
    free(pen);
}
