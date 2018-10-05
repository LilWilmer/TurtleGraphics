/******************************************************************************
* AUTH: William Payne
* FILE: draw.c
* LAST MOD: 05/10/18
* PURPOSE: not much of a purpose besides abstracting the use of effects.c.
*          Consider removing this c file all together.
******************************************************************************/
#include "draw.h"

/*****************************************************************************
* FUNCTION: runGCommand
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)               ~ Keeps track of data needed for line() and for
*                             command functions.
*   commands(LinkedList*)   ~ List of Graphics commands.
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
*****************************************************************************/
void executeGCommandList(Pen *pen, LinkedList *commands)
{
    GCommand *command = NULL;

    CLEAR_SCREEN;

    /*START NEW LOG BUGGER*/
    tlog(START_LOG);
    
    while(commands->count > 0)
    {
        command = removeFirst(commands);

        /*Running command*/
        (*((COMMANDFUNC)(command->executer)))(pen, command);

        /*Freeing command*/
        freeCommand(command);
    }
    /*CLEAR LOG BUGGER*/
    tlog(NULL);

    /*Place cursor back at bottom of the screen*/
    penDown();
}