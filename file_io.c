/******************************************************************************
* AUTH: William Payne
* FILE: file_io.c
* LAST MOD: 05/10/2018
* PURPOSE: Handle functions pertaining too reading/writing to and from files.
******************************************************************************/
#include "file_io.h"

/*****************************************************************************
* FUNCTION: readCommands
*-----------------------------------------------------------------------------
* IMPORTS: 
*   fileName(char*)         ~ File name of the turtle graphics command file.
*   commands(LinkedList*)   ~ List for holding each GCommand from the file.
*
* EXPORTS: 
*   success(int) ~ A number representing the success of the function.
*
* PURPOSE: 
*   Create GCommands structs using data read in from a file and store the 
*   structs into the commands list.
*
* ERROR CODES: 
*   0 ~ No errors occured.
*   1 ~ File doesn't exist.
*   2 ~ Read error occured.
*   3 ~ File failed to close.
*
*  NOTES:
*   If error occurs it is up to the user of this function the free the list.
*****************************************************************************/
int readCommands(char* fileName, LinkedList *commands)
{
    /*DECLARTIONS--------------*/
    int error = FALSE, success;
    int ii = 0;

    char BADOPEN[60];
    char BADREAD[60];
    char BADFORMAT[60];
    char BADCLOSE[60];
    char preservedLine[COMMAND_LENGTH];
    char line[COMMAND_LENGTH];
    char delim[] = " ";
    char *type = NULL, *data = NULL;

    /*INITALIZATIONS----------*/
    GCommand *newGCommand = NULL;
    FILE* f = NULL;

    /*perror() only takes a single string, need to strcat filename here*/
    sprintf(BADOPEN,"Error opening file: %s\n",fileName);
    sprintf(BADREAD,"Error reading from file: %s\n",fileName);
    sprintf(BADFORMAT,"Invalid file format: %s\n",fileName);
    sprintf(BADCLOSE,"Error closing file: %s\n",fileName);

    success = 0;

    /*OPEN------------------------------------------------------------------*/
    f = fopen(fileName,READ);

    /*ERROR HANDLING-------------------------*/
    if(f == NULL)
    {
        perror(BADOPEN);
        success = 1;
    }
    else if(ferror(f))
    {
        perror(BADREAD);
        success = 2;
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

            /*Gracefully skipping lines with a only a new line character*/
            if( strlen(line) > 1)
            {
                newGCommand = NULL;
                type = strtok(line,delim);
                data = strtok(NULL,delim);

                /*If a bad line is encountered terminate reading*/
                if(type != NULL && data != NULL && strtok(NULL,delim) == NULL)
                {
                    if(createGCommand(type, data, &newGCommand) == 0)
                    {
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
        if(ferror(f))
        {
            perror(BADREAD);
        }
        if(error == TRUE)
        {
            printf("%s",BADFORMAT);
            printf("\"%s\" HERE--->Line:%d\n", preservedLine, ii);
            success = 2;
        }
        newGCommand = NULL;
    }
    /*CLEAN UP------------------*/
    if(f != NULL && fclose(f))
    {
        /*CLOSE-------------------------------------------------------------*/
        perror(BADCLOSE);
        success = 3;
    }
    /*--------------------------*/
    return success;
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
int formatLog(char *line, char* type, Coord *startPos, Coord *endPos)
{
    sprintf(line, LOG_FORMAT, type, startPos->pos[0], startPos->pos[1]
           ,endPos->pos[0], endPos->pos[1]);

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
* NOTES: To empty 
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
* FUNCTION: emptyBuffer
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
int emptyBuffer(char ***logBuffer, int *logCount)
{
    int ii;
    appendStrings(LOG_FILE, *logBuffer, *logCount);
    for(ii = 0; ii < *logCount; ii++)
    {
        free((*logBuffer)[ii]);
        (*logBuffer)[ii] = NULL;
    }
    free(*logBuffer);
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
*   success(int)    ~ A Number representing an error code.
*
* PURPOSE: 
*   Append an array of strings at the end of the specified file.
*
* ERROR CODES: 
*   0 = No errors.
*   1 = File doesn't exist.
*   2 = Write error.
*   3 = Error closing file.
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
    int success;

    char BADOPEN[60];
    char BADWRITE[60];
    char BADCLOSE[60];
    FILE *f = NULL;

    sprintf(BADOPEN,"Error opening file, %s",fileName);
    sprintf(BADWRITE,"Error writing to file, %s",fileName);
    sprintf(BADCLOSE,"Error closing file, %s",fileName);
    
    f = fopen(fileName,APPEND);

    success = 0;

    /*ERROR HANDLING-------------------------*/
    if(f == NULL)
    {
        perror(BADOPEN);
        success = 1;
    }
    else if(ferror(f))
    {
        perror(BADWRITE);
        success = 2;
    }
    /*---------------------------------------*/
    else
    {
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
        }
    }

    /*If f == NULL it cannot be closed*/
    if(f != NULL)
    { 
        if(fclose(f))
        {
            /*The file was not closed correctly, nothing can be done*/
            perror(BADCLOSE);
            success = 3;
            /*It is the Lord who goes before you. He will be with you;
             he will not leave you or forsake you. Do not fear or be
             dismayed. - Deuteronomy 31:8”*/
        }
    }
    /*--------------------------*/
    return success;
}


