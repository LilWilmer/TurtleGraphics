/******************************************************************************
* AUTH: William Payne
* FILE: XXXXX
* LAST MOD: XXXXX
* PURPOSE: XXXXX
******************************************************************************/
#include "pen.h"

/*****************************************************************************
* FUNCTION: createPen
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	''
* EXPORTS: 
*   ''
* PURPOSE: 
*   --
* ERROR CODES: 
*   --
* NOTES: 
*   Pen must be freed before ending program
*****************************************************************************/
int createPen(Pen **pen)
{
    *pen = (Pen*)malloc(sizeof(Pen));

    (*pen)->position[0] = 0.0f;
    (*pen)->position[1] = 0.0f;
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
*   'pen'  ~ A pointer to the Pen struct to be freed.
*
* EXPORTS: none 
*
* PURPOSE: 
*   frees all heap data associated with the Pen struct.
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
