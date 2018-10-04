/*HEADER GUARD--------------------------------------------------------------*/
#ifndef G_COMMAND_H
#define G_COMMAND_H

/*INCLUDES------------------------------------------------------------------*/
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
#define LOG_ENTRY_LENGTH 100


/*TYPE DEFS AND STRUCTS-----------------------------------------------------*/


/*GRAPHICS COMMAND*/

typedef struct{
    VOID executer;  /*A pointer to a command function*/
    void *data;           /*Data will depend on the type of gCommand*/
}GCommand;
typedef int (*COMMANDFUNC)( Pen *, GCommand *);


/*ALLOCATER function pointer*/
typedef int (*ALLOCATER)(char *data, GCommand *gCommand);


/*FORWARD DECLARATIONS------------------------------------------------------*/
int createGCommand(char *type, char *data, GCommand **newGCommand);

/*COMMAND FUNCTIONS*/
int rotate( Pen *pen, GCommand *command);
int move(Pen *pen, GCommand *command);
int draw(Pen *pen, GCommand *command);
int colourFG(Pen *pen, GCommand *command);
int colourBG(Pen *pen, GCommand *command);
int changePattern(Pen *pen, GCommand *command);

/*plotter call-back function*/
void plotter(void *plotData);

int getAllocater(char *type, ALLOCATER allocaterPtr);

void freeCommand(GCommand *gCommand);

#endif