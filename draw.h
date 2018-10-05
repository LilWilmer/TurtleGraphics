/*****************************************************************************
* AUTH: William Payne
* FILE: XXXXX
* LAST MOD: XXXXX
* PURPOSE: XXXXX
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
* executeGCommandList():
* --- --- --- --- --- ---
* Runs through each GCommand struct passing itself along with the 'pen' to
* the function pointer it stores.
*/
void executeGCommandList(Pen *pen, LinkedList *commandSequence);

#endif