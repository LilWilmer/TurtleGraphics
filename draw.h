/*****************************************************************************
* AUTH: William Payne
* FILE: draw.h
* LAST MOD: 14/10/2018
* PURPOSE: Header file for draw.c
*****************************************************************************/
/*HEADER GUARD--------------------------------------------------------------*/
#ifndef DRAW_H
#define DRAW_H

/*INCLUDE STATEMENTS--------------------------------------------------------*/
#include "common.h"
#include "pen.h"
#include "linked_list.h"
#include "file_io.h"

/*FORWARD DECLARATIONS------------------------------------------------------*/
/**
* drawArt():
* --- --- --- --- --- ---
* Runs through each GCommand struct passing itself along with the 'pen' to
* the function pointer it stores.
*/
void drawArt(Pen *pen, LinkedList *commandSequence);

#endif