#include "user_input.h"

#define LENGTH 2
/*******************************************
* Function: readInt
*   Import: inputArr(void*), format(char[])
*   Export: none
*   Purpose: Fill inputArr based on format
*            String.
*******************************************
void readData(void *inputArr, char *format)
{
    int ii;
    char *dataType = (char*)calloc( LENGTH, sizeof(char));
    
    for(ii = 0; ii < strlen(format)+1; ii++) *Goes through each %? in format*
    {
        dataType[0] = '%';
        dataType[1] = format[ii];
        scanf(dataType,(int*)&inputArr[ii]);
    }

    free(dataType);
    dataType = NULL;
}*/

/***************************************
* Function: readInt
*  Imports: intPtr(int*), prompt(char*)
*  Exports: none
*  Purpose: Read in integer input from
*           user.
***************************************/
void readInt(int *intPtr, char *prompt)
{
    CLEAR_SCREEN;

    printf("%s",prompt);
    scanf("%d",intPtr);

    CLEAR_SCREEN;
}

/***************************************
* Function: readChar
*  Imports: charPtr(char*), prompt(char*)
*  Exports: none
*  Purpose: Read in character input from
*           user.
***************************************/
void readChar(char *charPtr, char *prompt)
{
    CLEAR_SCREEN;

    printf("%s",prompt);
    scanf("%c",charPtr);/*Its skipping first scan for some reason.*/
    scanf("%c",charPtr);

    CLEAR_SCREEN;
}

/***********************************************************
* FUNCTION: readString
*  IMPORTS: stringPtr(char*) length(int), prompt(char*)
*  EXPORTS: none
*  PURPOSE: Read in string from user
***********************************************************/
void readString(char* stringPtr, int length, char* prompt)
{
    char format[] = {'%', '1', 's'};

    CLEAR_SCREEN;

    sprintf(format+1,"%d",length);

    printf("%s",prompt);
    scanf(format,stringPtr);

    CLEAR_SCREEN;
}

