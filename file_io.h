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
#define LOG_FORMAT "%4s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n"
#define LOG_FILE "graphics.log"
#define LOG_ENTRY_LENGTH 100
#define START_LOG "---\n"
#define BUFFER_SIZE 100
#define COMMAND_LENGTH 100
#define TIME_ARRAY_LEN 4

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
* emptyBuffer():
* --- --- --- ---
* Calls appendStrings() to write logs to the LOG_FILE, resets the
* log counter and cleans up all memory used.
*/
int emptyBuffer(char ***logBuffer, int *logCount);

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
