/*****************************************************************************
 AUTH: William Payne
* FILE: g_command.c
* LAST MOD: 15/10/18
* PURPOSE: Functions for GCommand structs
*****************************************************************************/
#include "g_command.h"
#include "file_io.h"


/*STATIC FUNCTION FORWARD DECLARTIONS*/

/*GCOMMAND FUNCTIONS*/

/*Having the following function declared as static forces you to use them
 by dereferencing a function pointer in the GCommand structs allowing for 
 better validation*/

/**
* rotate():
* --- --- ---
* Calculates the angle from the 'command' data and either adds or 
* subtracts it from the current angle stored in 'pen'.
*/
static int rotate( Pen *pen, GCommand *command);

/**
* move():
* --- --- 
* Moves the cursor place by passing the coordinate data from 
* calculatePosition() to pen->positon.
*/
static int move(Pen *pen, GCommand *command);
/**
* draw():
* --- --- 
* Calculates the start and end position for line() to draw the pattern stored
* in 'pen' onto the terminal.
*/
static int draw(Pen *pen, GCommand *command);


/**
* colourFG():
* --- --- ---
* Sets the pen FG field to the command data and calls setFgColour in effects.c
*/
static int colourFG(Pen *pen, GCommand *command);

/**
* colourBG():
* --- --- --- 
* Sets the pen BG field to the command data and calls setBgColour in effects.c
*/
static int colourBG(Pen *pen, GCommand *command);

/**
* changePattern():
* --- --- --- ---
* Sets the pen field 'pattern' the command data.
*/
static int changePattern(Pen *pen, GCommand *command);
/*==END OF COMMAND FUNCTIONS==*/

/**
* allocateDouble():
* --- --- --- ---
* Allocates enough memory to hold a double to the GCommand and assigns the
* value at data to that memory.
*/
static int allocateDouble(char *data, GCommand *gCommand);

/**
* allocateInt():
* --- --- --- ---
* Allocates enough memory to hold an int to the GCommand and assigns the value
* at data to that memory.
*/
static int allocateInt(char *data, GCommand *gCommand);

/**
* allocateChar():
* --- --- --- ---
* Allocates enough memory to hold a double and assigns the value
* at data to that memory.
*/
static int allocateChar(char *data, GCommand *gCommand);

/*****************************************************************************
* FUNCTION: createGCommand
*-----------------------------------------------------------------------------
* IMPORTS:
*   type(char*)             ~ Contains the type of graphic command.
*   data(char*)             ~ Contains the data for the graphic command.
*   newGCommand(GCommand**) ~ New GCommand to be allocated memory and data.
*
* EXPORTS: 
*   status(int)    ~ Number indicating status of the function (errorcode)
*
* PURPOSE: 
*   Creates a GCommand struct and allocates the correct data depending on the
*   imported String 'type'.
*
* ERROR CODES: 
*   0 = Success.
*   1 = Invalid type.
*   2 = Invalid data.
*
* NOTES: 
*   newGCommand will be NULL if an error occurs.
*   newGCommand needs to be freed before the end of the program.
*****************************************************************************/
int createGCommand(char *type, char *data, GCommand **newGCommand)
{
    int status = 0;
    CommandFunc commandFuncPtr = NULL;
    AllocateFunc allocaterPtr = NULL;

    /*Formatting type to uppercase to match predefined type constants*/
    capitalize(type);

    /*Find and validate GCommand type*/
    if(strcmp(type, ROTATE) == 0)
    {
        /*Giving each command a function pointer to its command function
         prevents the need of using another if/switch statement to call the
         function*/
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
        status = 1;
    }

    /*Constructing newGCommand*/
    if(status == 0)
    {
        /*Allocating heap memory for GCommand struct*/
        *newGCommand = (GCommand*)malloc(sizeof(GCommand));

        /*Assigning the command function*/
        (*newGCommand)->executer = (VoidFunc)commandFuncPtr;

        /*Attempt to allocate and assign data to GCommand data*/
        if((*allocaterPtr)(data,*newGCommand) == 1)
        {
            /*ERROR - Data was invalid*/
            status = 2;
            freeCommand(*newGCommand);
        }
    }

    return status;
}

/*****************************************************************************
* STATIC FUNCTION: rotate
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ No errors.
*
* PURPOSE: 
*   Calculates the angle from the 'command' data and either adds or 
*   subtracts it from the current angle stored in 'pen'.
*
* NOTES: 
*   I'm pretty sure calculating the principal angle is pointless.
*   It could be easily validated if by adding or subtracting 360 off the angle
*   until it is within the range of -360 to +360 but its more if/else statements
*   and more processing that will only help in very extreme circumstances.
*****************************************************************************/
static int rotate( Pen *pen, GCommand *command)
{
    /*Converting angle to clockwise*/
    pen->angle += -1*(*(double*)(command->data));

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: move
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ No errors.
*
* PURPOSE: 
*   Moves the cursor place by passing the coordinate data from 
*   calculatePosition() to pen->positon.
*
* ERROR CODES: 
*   '0' ~ No errors.
*
* NOTES: I'm having trouble with the cursors accuracy, currently the realign
*        function appears to be solving the problem but choosing a tolerance
*        to realign on is not fully clear.
*   
*****************************************************************************/
static int move(Pen *pen, GCommand *command)
{
    double distance;
    Coord currPos = pen->position;
    Coord newPos = NEW_COORD;
    char logEntry[LOG_ENTRY_LENGTH];

    distance = *(double*)(command->data);


    /*Finding new cursor position.*/
    calculatePosition(&newPos, &pen->realPos, distance, pen->angle);

    /*assigning the new cursor position to the pen struct*/
    pen->realPos = newPos;
    pen->position.pos[0] = rounds(newPos.pos[0]);
    pen->position.pos[1] = rounds(newPos.pos[1]);

    /*If the the coordinates current position is to far out of line with its
     real position reset it.*/
    realign(&pen->realPos, &pen->position);

    /*LOGGING---------------------------------------------------------------*/
    formatLog(logEntry, DRAW, &currPos, &newPos);
    tlog(logEntry);

    /*TurtleGraphicsDebug*/
    #ifdef DEBUG
    penDown();
    fprintf(stderr,"%s",logEntry);
    #endif

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: draw
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ No errors.
*
* PURPOSE:
*   Calculates the start and end position for line() to draw the pattern stored
*   in 'pen' onto the terminal. 
*
* ERROR CODES: 
*   0 ~ No errors.
*
* NOTES: 
*   --
*****************************************************************************/
static int draw(Pen *pen, GCommand *command)
{
    int x1, y1, x2, y2;
    double distance;
    Coord currPos = pen->position;
    Coord realPos = pen->realPos;
    Coord newPos = NEW_COORD;
    Coord startPos = realPos;

    char logEntry[LOG_ENTRY_LENGTH];
    distance = *(double*)(command->data);

    /*Calculating the end point of line to be drawn*/
    /*The distance is reduced by one to remove a pattern plot at the final 
      position of the cursor - this has to be corrected after the plot*/
    calculatePosition(&newPos, &currPos, distance-1, pen->angle);

    /*Getting rounded coordinates for the line function*/
    x1 = rounds(currPos.pos[0]);
    y1 = rounds(currPos.pos[1]);
    x2 = rounds(newPos.pos[0]);
    y2 = rounds(newPos.pos[1]);

    /*Plotting the a line to the terminal*/
    line(x1, y1, x2, y2, &plotter, (void*)&(pen->pattern));

    /*Moving and correcting cursors location after plot*/
    calculatePosition(&newPos, &startPos, distance, pen->angle);
    pen->position.pos[0] = rounds(newPos.pos[0]);
    pen->position.pos[1] = rounds(newPos.pos[1]);
    pen->realPos = newPos;

    /*if the cursor has moved to far away from its real position it is
      realigned*/
    realign(&pen->realPos, &pen->position);

    /*LOGGING---------------------------------------------------------------*/
    formatLog(logEntry, DRAW, &startPos, &newPos);
    tlog(logEntry);

    /*TurtleGraphicsDebug*/
    #ifdef DEBUG
    penDown();
    fprintf(stderr,"%s",logEntry);
    #endif

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: colourFG
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ status.
*
* PURPOSE: 
*   Sets the pen FG field to the command data and calls setFgColour()
*
* NOTES: 
*   This function has no effect in TurtleGraphicSimple. 
*****************************************************************************/
static int colourFG(Pen *pen, GCommand *command)
{
    /*SKIPS IN TurtleGraphicsSimple*/
    #ifndef SIMPLE
    pen->fg = *(int*)(command->data); 
    setFgColour(pen->fg);
    #endif

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: colourBG
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0' ~ status.
*
* PURPOSE: 
*   Sets the pen FG field to the command data and calls setBgColour()
*
* NOTES: 
*   This function has no effect in TurtleGraphicSimple. 
*****************************************************************************/
static int colourBG(Pen *pen, GCommand *command)
{
    /*SKIPS IN TurtleGraphicsSimple*/
    #ifndef SIMPLE
    pen->bg = *(int*)(command->data); 
    setBgColour(pen->bg);
    #endif

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: changePattern
*-----------------------------------------------------------------------------
* IMPORTS: 
*   pen(Pen*)           ~ Pen struct tracks data for line() function.
*   command(GCommand*)  ~ GCommand struct contains the command data.
*
* EXPORTS: 
*   '0'     ~ status.
*
* PURPOSE: 
*   Sets the pen field 'pattern' the command data
*
*****************************************************************************/
static int changePattern(Pen *pen, GCommand *command)
{
    pen->pattern = *(char*)(command->data);
    return 0;
}

/*****************************************************************************
* FUNCTION: plotter
*-----------------------------------------------------------------------------
* IMPORTS: 
*   plotData(void*)  ~ A void pointer to a char that will be printed.
*
* EXPORTS: 
*   none
*
* PURPOSE: 
*   Prints a single character to the terminal (Will be used as a call back
*   function in effects.c).
*
* NOTES: 
*  plotData is void to allow any data to be passed through to a PLOTTER func.
*****************************************************************************/
void plotter(void *plotData)
{
    printf("%c", *(char*)plotData);
}

/*****************************************************************************
* STATIC FUNCTION: allocateDouble
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	data(char*)         ~ A String containing data for the GCommand Struct.
*   gCommand(GCommand*) ~ The GCommand struct.
*
* EXPORTS: 
*   status(int)    ~ Number representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 = No errors.
*   1 = Invalid data.
*
* NOTES: 
*   - 'data' should point to a string containing a single double value.
*   - I've chosen not to validate for very large numbers. I dont see it being
*     a big problem from the tests ive run.
*****************************************************************************/
static int allocateDouble(char *data, GCommand *gCommand)
{
    int status = 0;
    gCommand->data = malloc(sizeof(double));
    if((sscanf(data,"%lf",(double*)gCommand->data)) == 0)
    {
        /*If no items are scanned the data is invalid*/
        status = 1;
    }

    return status;
}

/*****************************************************************************
* STATIC FUNCTION: allocateInt
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	data(char*)         ~ A String containing data for the GCommand Struct
*   gCommand(GCommand*) ~ The GCommand struct
*
* EXPORTS: 
*   status(int)   ~ Number representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 = No errors.
*   1 = Invalid data.
*
* NOTES: 
*   - 'data' should point to a String containing a single int value.
*   - I've chosen not to validate for very large numbers. I dont see it being a
*     a big problem from the tests ive run.
*****************************************************************************/
static int allocateInt(char *data, GCommand *gCommand)
{
    int status = 0;

    gCommand->data = malloc(sizeof(int));
    if((sscanf(data,"%d",(int*)gCommand->data)) == 0)
    {
        /*If no items are scanned the data is invalid*/
        status = 1;
    }

    return status;
}

/*****************************************************************************
* STATIC FUNCTION: allocateChar
*-----------------------------------------------------------------------------
* IMPORTS: 
* 	data(char*)         ~ A String containing data for the GCommand Struct
*   gCommand(GCommand*) ~ The GCommand struct
*
* EXPORTS: 
*   status(int)    ~ Number representing the ERROR codes.
*
* PURPOSE: 
*   Allocates enough space on the heap to hold the data for the 
*   GCommand Struct and reads the data into that space.
*
* ERROR CODES: 
*   0 = No errors.
*   1 = Invalid data.
*
* NOTES: 
*   - 'data' should point to a single char.
*****************************************************************************/
static int allocateChar(char *data, GCommand *gCommand)
{
    int status = 0;

    gCommand->data = malloc(sizeof(char));
    if(sscanf(data,"%c",(char*)gCommand->data) == 0)
    {
        /*If no items are scanned the data is invalid*/
        status = 1;
    }

    return status;
}

/*****************************************************************************
* FUNCTION: freeCommand
*-----------------------------------------------------------------------------
* IMPORTS: 
*   gCommand(void*) ~ Graphics Command to be freed
*
* EXPORTS: 
*   status(int)    ~ Number representing the error code.
*
* PURPOSE: 
*   Frees heap memory from 'data' then frees the gCommand from the heap
*
* NOTES:
*   The function takes in a void pointer so that is matches FreeFunc data
*   type used by the generic LinkedList struct.
*****************************************************************************/
void freeCommand(void *gCommand)
{
    free(((GCommand*)gCommand)->data);
    free(((GCommand*)gCommand));
}

