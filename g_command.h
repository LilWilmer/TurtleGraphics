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

/*==COMMAND FUNCTIONS==*/
/**
* rotate():
* --- --- ---
* Calculates the angle from the 'command' data and either adds or 
* subtracts it from the current angle stored in 'pen'.
*/
int rotate( Pen *pen, GCommand *command);

/**
* move():
* --- --- 
* Moves the cursor place by passing the coordinate data from 
* calculatePosition() to pen->positon.
*/
int move(Pen *pen, GCommand *command);

/**
* draw():
* --- --- 
* Calculates the start and end position for line() to draw the pattern stored
* in 'pen' onto the terminal.
*/
int draw(Pen *pen, GCommand *command);

/**
* colourFG():
* --- --- ---
* Sets the pen FG field to the command data and calls setFgColour in effects.c
*/
int colourFG(Pen *pen, GCommand *command);

/**
* colourBG():
* --- --- --- 
* Sets the pen BG field to the command data and calls setBgColour in effects.c
*/
int colourBG(Pen *pen, GCommand *command);

/**
* changePattern():
* --- --- --- ---
* Sets the pen field 'pattern' the command data.
*/
int changePattern(Pen *pen, GCommand *command);
/*==END OF COMMAND FUNCTIONS==*/

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