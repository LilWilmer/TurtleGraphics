/*****************************************************************************
* AUTH: William Payne
* FILE: g_command.h
* LAST MOD: 05/10/2018
* PURPOSE: Header file for g_command.c
*****************************************************************************/
/*HEADER GUARD--------------------------------------------------------------*/
#ifndef G_COMMAND_H
#define G_COMMAND_H

/*INCLUDE STATMENTS---------------------------------------------------------*/
#include "common.h"
#include "pen.h"
#include "effects.h"

/*CONSTANTS-----------------------------------------------------------------*/

/*COMMAND TYPES*/
#define ROTATE "ROTATE"
#define MOVE "MOVE"
#define DRAW "DRAW"
#define FG "FG"
#define BG "BG"
#define PATTERN "PATTERN"

/*TYPE DEFS AND STRUCTS-----------------------------------------------------*/
/*----------------------------------------------------------------------------
* Graphics Command struct:
* ---   ---   ---   ---
* Tag: --
* Typedef: GCommand
* Purpose: Holds a function pointer and a pointer to an unknown piece of data
* FIELDS:
*   executer(VoidFunc)  ~ A pointer to a command function
*   data                ~ Data relevent to the command function
* ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---
*/
typedef struct{
    VoidFunc executer;
    void *data;
}GCommand;

/**
* CommandFunc function pointer:
* --- --- --- --- --- --- --- ---
* Function pointer to a command function e.g rotate(), move(), draw() ect...
*/
typedef int (*CommandFunc)( Pen *, GCommand *);


/**
* Allocater function pointer:
* --- --- --- --- --- --- --- 
* Function pointer to an allocater function in g_commands.c 
* (used in creating new GCommand structs)
*/
typedef int (*AllocateFunc)(char *data, GCommand *gCommand);


/*FORWARD DECLARATIONS------------------------------------------------------*/
/**
* createGCommand():
* --- --- --- ---
* Creates a GCommand struct and allocates the correct data depending on the
* imported String 'type'.
*/
int createGCommand(char *type, char *data, GCommand **newGCommand);

/**
* plotter():
* --- --- ---
* Prints a single character to the terminal (Will be used as a call back
* unction in effects.c).
*/
void plotter(void *plotData);

/**
* freeCommand():
* --- --- --- ---
* Frees heap memory from 'data' then frees the gCommand from the heap.
*/
void freeCommand(void *gCommand);

#endif