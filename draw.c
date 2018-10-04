/******************************************************************************
* AUTH: William Payne
* FILE: XXXXX
* LAST MOD: XXXXX
* PURPOSE: XXXXX
******************************************************************************/
#include "draw.h"

/*****************************************************************************
* FUNCTION: runGCommand
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'               ~ Pen struct pointer
*   'commandSequence'   ~ LinkedList containing the graphics command structs
*
* EXPORTS: 
*   void
*
* PURPOSE:
*   Runs through each GCommand struct
*  
* ERROR CODES:(Consider returning an int and come up with valid error codes)
*  --
*
* NOTES: 
*  -Current issue with the price plot of the pattern.
*  -Split case statements into serperate functions.
*****************************************************************************/
void executeGCommandList(Pen *pen, LinkedList *commands)
{
    GCommand *command = NULL;

    CLEAR_SCREEN;
    tlog("---\n");
    while(commands->count > 0)
    {
        command = removeFirst(commands);

        /*Running command*/
        (*((COMMANDFUNC)(command->executer)))(pen, command);

        /*Freeing command - note, the linked list node still exists*/
        freeCommand(command);
    }
    penDown();
}