/*START*/
#ifndef FILEIO_H
#define FILEIO_H

#include "common.h"
#include "linked_list.h"
#include "g_command.h"

#define READ "r"
#define WRITE "w"
#define APPEND "a"
#define LOG_FORMAT "%4s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n"
#define LOG_FILE "graphics.log"
#define LOG_ENTRY_LENGTH 100
#define ENTRY_LENGTH 20
#define TIME_ARRAY_LEN 4

int readCommands(char* fileName, LinkedList *commandSequence);
int tlog(char *line);
void formatLog(char *line, char* type, double *currPos, double *newPos);

#endif
/*END*/
