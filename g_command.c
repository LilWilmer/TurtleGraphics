/******************************************************************************
* AUTH: William Payne
* FILE: g_command.c
* LAST MOD: 04/10/18
* PURPOSE: Functions for GCommand structs
******************************************************************************/
#include "g_command.h"
#include "file_io.h"

/*STATIC METHODS FORWARD DECLARTIONS*/
static int allocateDouble(char *data, GCommand *gCommand);
static int allocateInt(char *data, GCommand *gCommand);
static int allocateChar(char *data, GCommand *gCommand);

/*****************************************************************************
* FUNCTION: createGCommand
*-----------------------------------------------------------------------------
* IMPORTS:
*   'type'          ~ A String containing the type of graphic command.
*   'data'          ~ A String containing the data for the graphic command.
*   'newGCommand'   ~ A GCommand struct to be allocated memory and data.
*
* EXPORTS: 
*   'success'       ~ An int returning the success of the function (errorcode)
*
* PURPOSE: 
*   Creates a GCommand struct and allocates the correct data depending on the
*   imported String 'type'.
*
* ERROR CODES: 
*   0 ~ Success.
*   1 ~ Invalid type.
*   2 ~ Invalid data.
*
* NOTES: 
*   newGCommand will be NULL if an error occurs.
*   newGCommand needs to be freed before the end of the program.
*****************************************************************************/
int createGCommand(char *type, char *data, GCommand **newGCommand)
{
    int success = 0;
    COMMANDFUNC commandFuncPtr = NULL;
    ALLOCATER allocaterPtr = NULL;

    /*Formatting type string*/
    capitalize(type);

    /*Find and validate GCommand type*/
    if(strcmp(type, ROTATE) == 0)
    {
        commandFuncPtr = &rotate;
        allocaterPtr = &allocateDouble;
    }
    else if(strcmp(type, MOVE) == 0)
    {
        commandFuncPtr = &move;
        allocaterPtr = &allocateDouble;
    }
    else if(strcmp(type, DRAW) == 0)
    {
        commandFuncPtr = &draw;
        allocaterPtr = &allocateDouble;
    }
    else if(strcmp(type, FG) == 0)
    {
        commandFuncPtr = &colourFG;
        allocaterPtr = &allocateInt;
    }
    else if(strcmp(type, BG) == 0)
    {
        commandFuncPtr = &colourBG;
        allocaterPtr = &allocateInt;
    }
    else if(strcmp(type, PATTERN) == 0)
    {
        commandFuncPtr = &changePattern;
        allocaterPtr = &allocateChar;
    }
    else
    {
        /*ERROR - Type was invalid, could not get ALLOCATOR*/
        success = 1;
    }

    /*Constructing newGCommand*/
    if(success == 0)
    {
        /*Allocating heap memory for GCommand struct*/
        *newGCommand = (GCommand*)malloc(sizeof(GCommand));

        /*Assigning the command function*/
        (*newGCommand)->executer = (VOID)commandFuncPtr;

        /*Attempt to allocate and assign data to GCommand data*/
        if((*allocaterPtr)(data,*newGCommand) == 1)
        {
            /*ERROR - Data was invalid*/
            success = 2;
            freeCommand(*newGCommand);
        }
    }

    return success;
}

/*****************************************************************************
* FUNCTION: rotate
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line().
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ No errors.
*
* PURPOSE: 
*   Calculates the principal angle from the 'command' data and either adds or 
*   subtracts it from the current angle stored in 'pen'.
*
* NOTES: 
*   I'm pretty sure calculating the principal angle is pointless.
*****************************************************************************/
int rotate( Pen *pen, GCommand *command)
{
    /*Converting angle to clockwise -consider doing this at the fileIO stage*/
    pen->angle += -1*(*(double*)(command->data));

    /*Finding the principal angle*/
    while(pen->angle < 0)
    {
        pen->angle += 360;
    }

    while(pen->angle >= 360)
    {
        pen->angle -= 360;
    }

    return 0;
}

/*****************************************************************************
* FUNCTION: draw
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line() function.
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ No errors.
*
* PURPOSE: 
*   Moves the cursor place by passing the coordinate data from 
*   calculatePosition() to pen->positon.
*
* ERROR CODES: 
*   LOG ERROR?
*
* NOTES: 
*   
*****************************************************************************/
int move(Pen *pen, GCommand *command)
{
    double *currPos = NULL;
    double newPos[2] = { 0.0f, 0.0f};
    double distance = 0.0f;
    char logEntry[LOG_ENTRY_LENGTH];

    currPos = pen->position;
    distance = *(double*)(command->data);

    calculatePosition(newPos, currPos, distance, pen->angle);

    formatLog(logEntry, MOVE, currPos, newPos);
    tlog(logEntry);

    pen->position[0] = newPos[0];
    pen->position[1] = newPos[1];

    return 0;
}

/*****************************************************************************
* FUNCTION: 
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line() function.
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   ''
*
* PURPOSE: 
*   --
*
* ERROR CODES: 
*   --
*
* NOTES: 
*   --
*****************************************************************************/
int draw(Pen *pen, GCommand *command)
{
    int x1, x2, y1, y2;
    double *currPos = NULL;
    double newPos[2] = { 0.0f, 0.0f};
    double distance = 0.0f;
    char logEntry[LOG_ENTRY_LENGTH];

    currPos = pen->position;
    distance = *(double*)(command->data);

    
    calculatePosition(newPos, currPos, distance-1, pen->angle);
    
    x1 = rounds(currPos[0]);
    y1 = rounds(currPos[1]);
    x2 = rounds(newPos[0]);
    y2 = rounds(newPos[1]);
    line(x1, y1, x2, y2, &plotter, (void*)&(pen->pattern));

    /*adjusting position after write*/
    pen->position[0] = newPos[0];
    pen->position[1] = newPos[1];
    currPos = pen->position;

    calculatePosition(newPos, currPos, 1, pen->angle);

    pen->position[0] = newPos[0];
    pen->position[1] = newPos[1];

    formatLog(logEntry, DRAW, currPos, newPos);
    /*NOTE: Consider adding each log to an array instead of opening and
        closing the file*/
    tlog(logEntry);

    #ifdef DEBUG
    penDown();
    printf("%s\n",logEntry);
    #endif

    return 0;
}

/*****************************************************************************
* FUNCTION: colourFG
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line() function.
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ success.
*
* PURPOSE: 
*   Sets the pen FG field to the command data
*
* NOTES: 
*   This function has no effect in TurtleGraphicSimple. 
*****************************************************************************/
int colourFG(Pen *pen, GCommand *command)
{
    #ifndef SIMPLE
    pen->fg = *(int*)(command->data); 
    setFgColour(pen->fg);
    #endif

    return 0;
}

/*****************************************************************************
* FUNCTION: colourBG
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line() function.
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ success.
*
* PURPOSE: 
*   Sets the pen FG field to the command data
*
* NOTES: 
*   This function has no effect in TurtleGraphicSimple. 
*****************************************************************************/
int colourBG(Pen *pen, GCommand *command)
{
    #ifndef SIMPLE
    pen->bg = *(int*)(command->data); 
    setBgColour(pen->bg);
    #endif

    return 0;
}

/*****************************************************************************
* FUNCTION: changePattern
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'pen'       ~ Pen struct tracks data for line() function.
*   'command'   ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ success.
*
* PURPOSE: 
*   Sets the pen field 'pattern' the command data
*
*****************************************************************************/
int changePattern(Pen *pen, GCommand *command)
{
    pen->pattern = *(char*)(command->data);
    return 0;
}

/*****************************************************************************
* FUNCTION: getAllocater
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	'type'          ~ String containing the type of ALLOCATER needed
*   'allocaterPtr'  ~ Function pointer to ALLOCATER functions.
*
* EXPORTS:
*   'success'   ~ An int representing an error code.
*
* PURPOSE: 
*   Matches 'type' to either ROTATE, MOVE, DRAW, FG, BG or PATTERN and assigns
*   the appropriate ALLOCATER function allocaterPtr.
*
* ERROR CODES: 
*   0 ~ No errors.
*   1 ~ Invalid type.
*
* NOTES: 
*   --
*****************************************************************************/
int getAllocater(char *type, ALLOCATER allocaterPtr)
{
    int success = 0;

    if((strstr(ROTATE, type)) || (strstr(MOVE, type))
    || (strstr(DRAW, type)))
    {
        allocaterPtr = &allocateDouble;
    }
    else if ((strstr(FG, type)) || (strstr(BG, type)))
    {
        allocaterPtr = &allocateInt;
    }
    else if(strstr(PATTERN, type))
    {
        allocaterPtr = &allocateChar;
    }
    else /*ERROR - Imported type is invalid*/
    {
        success = 1;
    }

    return success;
}

/*****************************************************************************
* FUNCTION: plotter
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'plotData'  ~ A void pointer to a char that will be printed.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Prints a single character to the terminal (Will be used as a call back
*   function in effects.c).
*
* NOTES: 
*  --
*****************************************************************************/
void plotter(void *plotData)
{
    printf("%c", *(char*)plotData);
}

/*****************************************************************************
* FUNCTION: allocateDouble
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	'data'      ~ A String containing data for the GCommand Struct
*   'gCommand'  ~ The GCommand struct
*
* EXPORTS: 
*   'success'   ~ Int representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 ~ No errors.
*   1 ~ Invalid data.
*
* NOTES: 
*   --
*****************************************************************************/
static int allocateDouble(char *data, GCommand *gCommand)
{
    int success = 0;
    gCommand->data = malloc(sizeof(double));
    if((sscanf(data,"%lf",(double*)gCommand->data)) == 0)
    {
        success = 1;
    }

    return success;
}

/*****************************************************************************
* FUNCTION: allocateInt
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	'data'      ~ A String containing data for the GCommand Struct
*   'gCommand'  ~ The GCommand struct
*
* EXPORTS: 
*   'success'   ~ Int representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 ~ No errors.
*   1 ~ Invalid data.
*
* NOTES: 
*   --
*****************************************************************************/
static int allocateInt(char *data, GCommand *gCommand)
{
    int success = 0;

    gCommand->data = malloc(sizeof(int));
    if((sscanf(data,"%d",(int*)gCommand->data)) == 0)
    {
        success = 1;
    }

    return success;
}

/*****************************************************************************
* FUNCTION: allocateChar
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	'data'      ~ A String containing data for the GCommand Struct
*   'gCommand'  ~ The GCommand struct
*
* EXPORTS: 
*   'success'   ~ Int representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 ~ No errors.
*   1 ~ Invalid data.
*
* NOTES: 
*   --
*****************************************************************************/
static int allocateChar(char *data, GCommand *gCommand)
{
    int success = 0;

    gCommand->data = malloc(sizeof(char));
    if(sscanf(data,"%c",(char*)gCommand->data) == 0)
    {
        success = 1;
    }

    return success;
}

/*****************************************************************************
* FUNCTION: freeCommand
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'gCommand'  ~ Graphics Command to be freed
*
* EXPORTS: 
*   'success'   ~ Int representing the error code.
*
* PURPOSE: 
*   Frees heap memory from 'data' then frees the gCommand from the heap
*
*****************************************************************************/
void freeCommand(GCommand *gCommand)
{
    free(gCommand->data);
    free(gCommand);
}
