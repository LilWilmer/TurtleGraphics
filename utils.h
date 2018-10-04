/*START FILE*/
#ifndef MYUTILS_H
#define MYUTILS_H

#include<math.h>

/*CONSTANTS-----------------------------------------------------------------*/
#define FALSE 0
#define TRUE !FALSE
#define PI 3.14159265358979323846

/*MACROS--------------------------------------------------------------------*/
#define CAPITALIZE(a) ((a)-32)
#define LOWERCASE(a) ((a)+32)
#define E(x) printf("line:%d\n",x);fflush(stdout);
#define CLEAR_SCREEN printf("\033[H\033[2J")

/*TYPEDEFS------------------------------------------------------------------*/
typedef void (*VOID)(void);

/*FORWARD DECLARTIONS-------------------------------------------------------*/
void capitalize( char *text);

/*MATH FUNCTIONS*/
int rounds(double num);
void convertToRadians( double *angle);
void calculatePosition( double *newPos, double *currPos
                      , double distance, double angle);


#endif
/*END FILE*/

