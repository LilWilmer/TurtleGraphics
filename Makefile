##############################################################################
# MAKEFILE: TurtleGraphics
# AUTH: William Payne
# LAST MOD: 18/09/18
##############################################################################

#CONSTANTS:
CC = gcc
CF = -Wall -Werror -ansi -pedantic -g
OBJ = main.o effects.o file_io.o draw.o linked_list.o pen.o user_input.o\
      utils.o
G_COMMAND_PREREQ = g_command.c g_command.h common.h effects.h file_io.h pen.h\
				   utils.h
EXEC = TurtleGraphics
EXEC_S = TurtleGraphicsSimple
EXEC_D = TurtleGraphicsDebug

ALL_EXEC = $(EXEC) $(EXEC_S) $(EXEC_D)

#RULES

all : $(ALL_EXEC)

$(EXEC) : $(OBJ) g_command.o
	$(CC) $(OBJ) g_command.o -o $(EXEC) -lm

$(EXEC_S) : $(OBJ) g_command_S.o
	$(CC) $(OBJ) g_command_S.o -o $(EXEC_S) -lm

$(EXEC_D) : $(OBJ) g_command_D.o
	$(CC) $(OBJ) g_command_D.o -o $(EXEC_D) -lm

main.o : main.c common.h draw.h file_io.h g_command.h linked_list.h pen.h utils.h
	$(CC) -c main.c $(CF)

draw.o : draw.c draw.h pen.h linked_list.h file_io.h common.h utils.h
	$(CC) -c draw.c $(CF)

linked_list.o : linked_list.c linked_list.h g_command.h common.h utils.h
	$(CC) -c linked_list.c $(CF)

pen.o : pen.c pen.h common.h utils.h
	$(CC) -c pen.c $(CF)

file_io.o : file_io.c file_io.h common.h g_command.h linked_list.h utils.h
	$(CC) -c file_io.c $(CF)

#TURTLE GRAPHICS VANILLA
g_command.o : $(G_COMMAND_PREREQ)
	$(CC) -c g_command.c $(CF)

#TURTLE GRAPHICS SIMPLE
g_command_S.o : $(G_COMMAND_PREREQ)
	$(CC) -c g_command.c -o g_command_S.o -DSIMPLE=1 $(CF)
	
#TURTLE GRAPHICS DEBUG
g_command_D.o : $(G_COMMAND_PREREQ)
	$(CC) -c g_command.c -o g_command_D.o -DDEBUG=1 $(CF)

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CF)

clean :
	rm -f $(EXEC) $(OBJ) g_command.o
