/*****************************************************************************
* AUTH: William Payne
* FILE: file_io.h
* LAST MOD: 05/10/2018
* PURPOSE: Header file for file_io.c
*****************************************************************************/
/*HEADER GUARD--------------------------------------------------------------*/
#ifndef FILEIO_H
#define FILEIO_H

/*INCLUDE STATEMENTS--------------------------------------------------------*/
#include "common.h"
#include "linked_list.h"
#include "g_command.h"

/*CONSTANTS-----------------------------------------------------------------*/
#define READ "r"
#define WRITE "w"
#define APPEND "a"
#define LOG_FORMAT "%4s (%8.3f,%8.3f)-(%8.3f,%8.3f)\n"
#define LOG_FILE "graphics.log"
#define LOG_ENTRY_LENGTH 100
#define START_LOG "---\n"
#define BUFFER_SIZE 100
#define COMMAND_LENGTH 100
#define TIME_ARRAY_LEN 4

typedef enum IO_Status{
    SUCCESS = 0,
    OPEN_ERROR = 1,
    READ_ERROR = 2,
    WRITE_ERROR = 3,
    CLOSE_ERROR = 4,
    INVALID_FORMAT = 5,
    EMPTY_FILE = 6
}IO_Status;

/*FORWARD DECLARTIONS-------------------------------------------------------*/
/**
* readCommands():
* --- --- --- ---
* Create GCommands structs using data read in from a file and store the 
* structs into the commands list.
* ERROR CODES: 
*   0 ~ No errors occured.
*   1 ~ File doesn't exist.
*   2 ~ Read error occured.
*   3 ~ File failed to close.
*/
int readCommands(char* fileName, LinkedList *commandSequence);

/**
* formatLog():
* --- --- --- ---
* Formats two Coordinates using LOG_FORMAT into the String 'line' with 
* sprintf() creating a log entry.
*/
int formatLog(char *line, char* type, Coord *currPos, Coord *newPos);

/**
* tLog(): (turtle log)
* --- --- --- --- --- ---
* Compile an array of logs then prints them to graphics.log
*/
int tlog(char *line);



/**
* appendStrings():
* --- --- --- ---
* Append an array of strings at the end of the specified file.
* ERROR CODES: 
*   0 = No errors.
*   1 = File doesn't exist.
*   2 = Write error.
*   3 = Error closing file.
*/
int appendStrings(char *fileName, char **strings, int stringCount);

#endif
/*END*/
