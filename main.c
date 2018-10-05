/******************************************************************************
* AUTH: William Payne
* FILE: main.c
* LAST MOD: 04/10/18
* PURPOSE: tis the main
******************************************************************************/
#include "common.h"
#include "pen.h"
#include "g_command.h"
#include "linked_list.h"
#include "file_io.h"
#include "draw.h"

/*****************************************************************************
* FUNCTION: main
*-----------------------------------------------------------------------------
* IMPORTS: none
*   argc(int)       ~ The number of command line arguments as an int.
*   argv(char**)    ~ The command line arguments in a string array.
*
* EXPORTS: 
*   '0' ~ Function succeeded.
*
* PURPOSE: 
*   Main function for TurtleGraphics
*
* NOTES: 
*   --
*****************************************************************************/
int main( int argc, char **argv)
{
    Pen *pen = NULL;
    LinkedList *commands = NULL;

    /*Only takes a single command line argument*/
    if(argc != 2)
    {
        printf("Usage: ./TurtleGraphics a\n");
        printf("    where:\n");
        printf("    a is the file name\n");
    }
    if(createPen(&pen) && createList(&commands))
    {
        commands->freeValuePtr = &freeCommand;
        if(readCommands(argv[1], commands) == 0)
        {
            executeGCommandList(pen, commands);
            setColourDefault();
        }

    }
    if(pen != NULL)
    {
        freePen(pen);
    }
    if(commands != NULL)
    {
        completeFreeList(commands);
    }

    return 0;
}
