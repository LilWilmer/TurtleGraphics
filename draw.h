#ifndef DRAW_H
#define DRAW_H

#include "common.h"
#include "pen.h"
#include "linked_list.h"
#include "file_io.h"

void executeGCommandList(Pen *pen, LinkedList *commandSequence);

#endif