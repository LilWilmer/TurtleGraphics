/******************************************************************************
* AUTH: William Payne
* FILE: file_io.c
* LAST MOD: 14/10/2018
* PURPOSE: Handle functions pertaining too reading/writing to and from files.
******************************************************************************/
#include "file_io.h"

/*STATIC FORWARD DECLARATIONS*/
/**
* emptyBuffer():
* --- --- --- ---
* Calls appendStrings() to write logs to the LOG_FILE, resets the
* log counter and cleans up all memory used.
*/
static int emptyBuffer(char ***logBuffer, int *logCount);

/*****************************************************************************
* FUNCTION: readCommands
*-----------------------------------------------------------------------------
* IMPORTS: 
*   fileName(char*)         ~ File name of the turtle graphics command file.
*   commands(LinkedList*)   ~ List for holding each GCommand from the file.
*
* EXPORTS: 
*   status(int) ~ A number representing the status of the function.
*
* PURPOSE: 
*   Create GCommands structs using data read in from a file and store the 
*   structs into the commands list.
*
* ERROR CODES: 
*   SUCCESS         = 0 ~ No errors occured.
*   OPEN_ERROR      = 1 ~ File doesn't exist.
*   READ_ERROR      = 2 ~ Read error occured.
*   CLOSE_ERROR     = 4 ~ File failed to close.
*   INVALID_FORMAT  = 5 ~ File format is not valid.
*   EMPTY_FILE      = 6 ~ File is empty.
*
*  NOTES:
*   If an error occurs it is up to the user of this function the free the list.
*   i.e. the list will contain all the commands successfully read.
*****************************************************************************/
int readCommands(char *fileName, LinkedList *commands)
{
    /*DECLARTIONS--------------*/
    IO_Status status;
    int error;
    int ii;

    /*I needed these to be string i could modify to allow the file name to be
     be added. - a normal printf() could use %s %s but the perror method only
     takes a single string*/
    char BADOPEN[60];
    char BADREAD[60];
    char BADFORMAT[60];
    char EMPTYFILE[60];
    char BADCLOSE[60];
    char preservedLine[COMMAND_LENGTH];
    char line[COMMAND_LENGTH];
    char delim[] = " ";
    char *type = NULL, *data = NULL;

    GCommand *newGCommand = NULL;
    FILE* f = NULL;

    /*perror() only takes a single string, need to strcat filename here*/
    sprintf(BADOPEN,"Error opening file: %s\n",fileName);
    sprintf(BADREAD,"Error reading from file: %s\n",fileName);
    sprintf(BADFORMAT,"Invalid file format: %s\n",fileName);
    sprintf(EMPTYFILE,"File is empty: %s\n",fileName);
    sprintf(BADCLOSE,"Error closing file: %s\n",fileName);

    status = SUCCESS;
    error = FALSE;
    ii = 0;

    /*OPEN------------------------------------------------------------------*/
    f = fopen(fileName,READ);

    /*ERROR HANDLING-------------------------*/
    if(f == NULL)
    {
        perror(BADOPEN);
        status = OPEN_ERROR;
    }
    else if(ferror(f))
    {
        perror(BADREAD);
        status = READ_ERROR;
    }
    /*---------------------------------------*/
    else
    {
        while(error == FALSE && !ferror(f) && fgets(line,COMMAND_LENGTH,f) != NULL)
        {
            /*Keeping track of the line number for an error report*/
            ii++;

            /*REMOVES TRAILING new line characters*/
            strtok(line,"\n");

            /*Preserves line for an error report if necessary*/
            strcpy(preservedLine, line);

            /*Skipping lines with a only a new line character*/
            if(line[0] != '\n')
            {
                newGCommand = NULL;
                type = strtok(line,delim);
                data = strtok(NULL,delim);

                /*If a bad line is encountered terminate reading*/
                if(type != NULL && data != NULL && strtok(NULL,delim) == NULL)
                {
                    if(createGCommand(type, data, &newGCommand) == 0)
                    {
                        /*newGCommand enters the queue of commands*/
                        insertLast(commands, newGCommand);
                    }
                    else
                    {
                        error = TRUE;
                    }
                }
                else
                {
                    error = TRUE;
                }
            }
        }
        if(ferror(f))/*File reading error.*/
        {
            perror(BADREAD);
        }
        if(error == TRUE)/*File format is invalid.*/
        {
            fprintf(stderr,"%s",BADFORMAT);
            fprintf(stderr,"\"%s\" HERE--->Line:%d\n", preservedLine, ii);
            status = INVALID_FORMAT;
        }
        else if(commands->count == 0)
        {
            fprintf(stderr,"%s",EMPTYFILE);
            status = EMPTY_FILE;
        }
        newGCommand = NULL;
    }
    /*CLEAN UP------------------*/
    if(f != NULL && fclose(f))
    {
        /*CLOSE-------------------------------------------------------------*/
        perror(BADCLOSE);
        status = CLOSE_ERROR;
    }
    /*--------------------------*/
    return status;
}

/*****************************************************************************
* FUNCTION: formatLog
*-----------------------------------------------------------------------------
* IMPORTS: 
*   line(char*)         ~ String to be printed to.
*   type(char*)         ~ String containing the command type e.g. "DRAW".
*   startPos(Coord*)    ~ Coord struct containg the starting position.
*   endPos(Coord*)      ~ Coord struct containing the end position.
*
* EXPORTS: 
*   '0'
*
* PURPOSE: 
*   Formats two Coordinates using LOG_FORMAT into the String 'line' with 
*   sprintf() creating a log entry.
*
* ERROR CODES: 
*
*  --
* NOTES: 
*   Using Coord structs lets the function validate that the array is of 
*   size 2.
*****************************************************************************/
int formatLog(char *line, char *type, Coord *startPos, Coord *endPos)
{
    double x1, x2, y1, y2;

    x1 = startPos->pos[0];
    y1 = startPos->pos[1];
    x2 = endPos->pos[0];
    y2 = endPos->pos[1];

    /*Keeping in 'negative 0' I dont know how to get rid of them*/
    sprintf(line, LOG_FORMAT, type, x1, y1, x2, y2);

    return 0;
}

/*****************************************************************************
* FUNCTION: tLog (turtle log)
*-----------------------------------------------------------------------------
* IMPORTS: 
*   log(char*)  ~ String to be printed to graphics.log
*
* EXPORTS: 
*   '0'   ~Int representing an error code.
*
* PURPOSE: 
*   Compile an array of logs then prints them to graphics.log
*
* ERROR CODES: 
*  --
*
* NOTES:
*   To empty the buffer pass in NULL.
*
*   Log data can be compiled here from anywhere in the program without passing
*   around a pointer to store the logs (or without opening file on every log)
*****************************************************************************/
int tlog( char *log)
{
    /*Just need a static pointer, I dont want to put all the logs into global
     storage*/
    static int logCount = 0;
    static char **logBuffer = NULL;

    /*IF THE LOG BUFFER IS NULL i.e. not in use, allocate memory*/
    if(logBuffer == NULL && log != NULL)
    {
        logBuffer = (char**)malloc(BUFFER_SIZE*sizeof(char*));
    }

    /*IF THE IMPORTED LOG IS NULL, empty the buffer and free all memory used*/
    if(log == NULL)
    {
        /*If logCount is 0, logBuffer will be NULL. No further action is
         needed*/
        if(logCount != 0)
        {
            emptyBuffer(&logBuffer, &logCount);
        }
    }
    else
    {
        /*Keep track of the number of logs in the buffer*/
        logCount++;

        /*Allocating enough room to hold the passed in log string
        (-1 for array indexing)              (+1 for the null terminator)*/
        logBuffer[logCount-1] = (char*)malloc(sizeof(char)*(strlen(log)+1));

        /*Copy contents from log to the newely malloced logBuffer[element]*/
        strcpy(logBuffer[logCount-1],log);

        /*When the log buffer is filled, empty and free all memory used*/
        if(logCount == BUFFER_SIZE)
        {
            emptyBuffer(&logBuffer, &logCount);
        }
    }

    return 0;
}

/*****************************************************************************
* STATIC FUNCTION: emptyBuffer
*-----------------------------------------------------------------------------
* IMPORTS: 
*   logBuffer(char***)  ~ Pointer to a String array containing log strings.
*   logCount(int*)      ~ Pointer to the The number of logs in the array .
*
* EXPORTS: 
*   '0'
*
* PURPOSE: 
*   Calls appendStrings() to write logs to the LOG_FILE, resets the
*   log counter and cleans up all memory used.
*
* ERROR CODES: 
*   THINK
*
* NOTES: 
*   --
*****************************************************************************/
static int emptyBuffer(char ***logBuffer, int *logCount)
{
    int ii;

    /* writing to the log file*/
    appendStrings(LOG_FILE, *logBuffer, *logCount);

    /*Clearing buffer*/
    for(ii = 0; ii < *logCount; ii++)
    {
        free((*logBuffer)[ii]);
        (*logBuffer)[ii] = NULL;
    }
    free(*logBuffer);

    /*Removing pointer to freed memory and resetting log count for next use*/
    *logBuffer = NULL;
    *logCount = 0;

    return 0;
}

/*****************************************************************************
* FUNCTION: appendStrings
*-----------------------------------------------------------------------------
* IMPORTS: 
*   fileName(char*)     ~ Name of file to be appended.
*   strings(char**)     ~ String array to be appended at the end of the file.
*   stringCount(int)    ~ Number of strings in array.
*
* EXPORTS: 
*   status(int)    ~ A Number representing an error code.
*
* PURPOSE: 
*   Append an array of strings at the end of the specified file.
*
* ERROR CODES: 
*   SUCCESS     = 0 ~ No errors.
*   OPEN_ERROR  = 1 ~ File doesn't exist.
*   WRITE_ERROR = 3 ~ Write error.
*   CLOSE_ERROR = 4 ~ Error closing file.
*
* NOTES: (METHOD APPENDS A PRE-EXISTING FILE)
*   MAKE THIS MODULE GENERIC
*   MAKE the new tLog() call printline,
*   MAKE the new tLog() have the persistant pointer
*   Consider creating a persistant pointer to linked list (logBuffer) and dump
*   the logs once it reaches a high enough count
*****************************************************************************/
int appendStrings(char *fileName, char **strings, int stringCount)
{
    int ii;
    IO_Status status;

    char BADOPEN[60];
    char BADWRITE[60];
    char BADCLOSE[60];
    FILE *f = NULL;

    /*Appending file name to the end of error messages*/
    sprintf(BADOPEN,"Error opening file: %s",fileName);
    sprintf(BADWRITE,"Error writing to file: %s",fileName);
    sprintf(BADCLOSE,"Error closing file: %s",fileName);
    
    f = fopen(fileName,APPEND);

    status = SUCCESS;

    /*Error opening file*/
    if(f == NULL)
    {
        perror(BADOPEN);
        status = OPEN_ERROR;
    }
    else if(ferror(f))
    {
        /*Write error occured*/
        perror(BADWRITE);
        status = WRITE_ERROR;
    }
    else
    {
        /*Looping through the buffer printing adding each line to the file*/
        ii = 0;
        while(ii < stringCount && !ferror(f))
        {
            fputs(strings[ii],f);
            ii++;
        }
        fflush(f);

        /*Checking to see if line was written correctly*/
        if(ferror(f))
        {
            perror(BADWRITE);
            status = WRITE_ERROR;
        }
    }

    /*If f == NULL it cannot be closed*/
    if(f != NULL)
    { 
        if(fclose(f))
        {
            /*The file was not closed correctly, nothing can be done*/
            perror(BADCLOSE);
            status = CLOSE_ERROR;
        }
    }
    /*--------------------------*/
    return status;
}

