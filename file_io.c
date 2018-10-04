/******************************************************************************
* AUTH: William Payne
* FILE: XXXXX
* LAST MOD: XXXXX
* PURPOSE: XXXXX
******************************************************************************/
#include "file_io.h"

/*****************************************************************************
* FUNCTION: readCommands
*-----------------------------------------------------------------------------
*  IMPORTS: 
*  'fileName' ~ A String containing the filename of the diary file.
*  'diary'    ~ A Diary struct* for holding the contents of the diary file.
*
*  EXPORTS: 
*  'success' ~ An int representing the success of the function.
*
*  PURPOSE: 
*   Read in entries from a diary and store them in a Entry struct.
*
*  ERROR CODES: 
*  -1 ~ Unknown error occured.
*   0 ~ No errors occured.
*   1 ~ File doesn't exist.
*   2 ~ Read error occured.
*   3 ~ File failed to close.
*   4 ~ Multiple errors occured.
*
*  NOTES:
*   --
*****************************************************************************/
int readCommands(char* fileName, LinkedList *commandSequence)
{
    /*DECLARTIONS--------------*/
    int error = FALSE, success;
    int ii = 0;

    char BADOPEN[60];
    char BADREAD[60];
    char BADFORMAT[60];
    char BADCLOSE[60];
    char preservedLine[ENTRY_LENGTH];
    char line[ENTRY_LENGTH];
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

    success = TRUE;

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
        while(error == FALSE && !ferror(f) && fgets(line,ENTRY_LENGTH,f) != NULL)
        {
            /*Keeping track of the line number for an error report*/
            ii++;

            /*REMOVES TRAILING new line characters*/
            strtok(line,"\n");

            /*Preserves line for an error report if necessary*/
            strcpy(preservedLine, line);

            if( strlen(line) > 1)
            {
                newGCommand = NULL;
                type = strtok(line,delim);
                data = strtok(NULL,delim);

                if(type != NULL && data != NULL && strtok(NULL,delim) == NULL)
                {
                    if(createGCommand(type, data, &newGCommand) == 0)
                    {
                        insertLast(commandSequence, newGCommand);
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
            success = FALSE;
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
* FUNCTION: tLog 
*-----------------------------------------------------------------------------
* IMPORTS: 
*   'line'  ~ String to be printed to graphics.log
*
* EXPORTS: 
*   'success'   ~Int representing an error code.
*
* PURPOSE: 
*   Print a single string to a txt file (OK MAKE THIS SHIT GENERIC)
*
* ERROR CODES: 
*  --
*
* NOTES: 
*   MAKE THIS MODULE GENERIC
*   MAKE the new tLog() call printline,
*   MAKE the new tLog() have the persistant pointer
*   Consider creating a persistant pointer to linked list (logCache) and dump
*   the logs once it reaches a high enough count
*****************************************************************************/
int tlog( char *line)
{
    int success;

    char BADOPEN[60];
    char BADWRITE[60];
    char BADCLOSE[60];
    FILE *f = NULL;

    sprintf(BADOPEN,"Error opening file, %s",LOG_FILE);
    sprintf(BADWRITE,"Error writing to file, %s",LOG_FILE);
    sprintf(BADCLOSE,"Error closing file, %s",LOG_FILE);
    
    f = fopen(LOG_FILE,APPEND);

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
        fputs(line,f);

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

/*****************************************************************************
* FUNCTION: formatLog
*-----------------------------------------------------------------------------
* IMPORTS: 
*  ''
* EXPORTS: 
*  ''
* PURPOSE: 
*  --
* ERROR CODES: 
*  --
* NOTES: 
*  --
*****************************************************************************/
void formatLog(char *line, char* type, double *currPos, double *newPos)
{
    sprintf(line, LOG_FORMAT, type, currPos[0], currPos[1]
           ,newPos[0], newPos[1]);
}
