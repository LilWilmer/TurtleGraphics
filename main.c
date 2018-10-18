/******************************************************************************
* AUTH: William Payne
* FILE: main.c
* LAST MOD: 04/10/18
* PURPOSE: main function for TurtleGraphics
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

    /*Checking for correct number of command-line arguments*/
    if(argc != 2)
    {
        printf("Usage: ./TurtleGraphics a\n");
        printf("    where:\n");
        printf("    a is the file name\n");
    }
    else if(!createPen(&pen) && !createList(&commands))
    {
        /*Assigning a GCommand free function to the generic linked list*/
        commands->freeFunc = &freeCommand;
        
        if(!readCommands(argv[1], commands))
        {
            /*Execute commands if read correctly*/
            drawArt(pen, commands);
            
            /*Sets the terminals colours back to default after execution.*/
            setColourDefault();
        }
    }
    /*CLEAN UP*/
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
