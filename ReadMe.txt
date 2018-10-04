Hi Will, Get ready for your best program yet!!

First Things First

DOCUMENTATION:
    -Each function and dataType must have a comment including:
        -Purpose
        -How it works
        -How it relates to other functions
    -Throughly comment code with /*...*/

TASK DETAILS:

    INPUT_FILE:
        -Accept command line parameter: Name of file containing graphics commands
        -Read the contents of file into 'linked list' see..
        -The file will consist of a sequence of commands, 1 per line
        -THERE IS NO LENGTH INDICATOR
        Commands: θeR = angle, deR = distance, ieZ = colour code, c = non-space char (NON-CASE SENSISTIVE)
            -ROTATE θ
            -MOVE d
            -DRAW d
            -FG i
            -BG i
            -PATTERN c
        -Must handle errors (including but not limited to)
            -File doesnt exist
            -File is empty
            -Lines starting without command
            -Incorrect number of params for a command
            -Incorrect datatype for a command

    TURTLE_GRAPHICS:
        -Keep track of changing information
            -Position(x,y)
                -Every command will start at a specified x,y
                -DRAW and MOVE change the current position
                -Starting pos is 0,0 (top left of screen)

            -Angle(θ): Basic directions 0 = right, 90 = up, 180 = left, 270 = down;
                -Initial angle is 0
                -ROTATE will + or - from current angle

            -Forground/Background colour(i): Forground 0-15, Backround 0-7
                -Initial Background = BLACK
                -Initial Forground = WHITE
                -BG and FG (pretty obvi)
                -Used everytime when placing a character

            -Pattern(c)
                -Inital pattern = '+'
                -PATTERN changes the current character

    EXISTING_FUNCTIONS: (effects.c effects.h)
        -line():
            void line(int x1, int y1, int x2, int y2, PlotFunc plotter, void *plotData);
            {
                This will draw a lone from coords(x1,y1) to (x2,y2)
                typedef void (*Plotfunc)(void *plotData);
                -The plotter will have to generate appropriate terminal output
                void *plotData is passed to PlotFunc plotter(this lets us pass any desired data)
            }
        -void setFgColour(int i)
        -void setBgColour(int i)
        -void clearScreen()
        -void penDown()-moves cursor to the bottom of the screen(drawing complete)

    LOG_FILE: graphics.log
        -Must 'append'(not overwrite) graphics.log
        -First line after existing contents "---"
        -Displays the prior and post results of MOVE and DRAW commands
            MOVE (x1,y1)-(x2,y2)
            DRAW (x1,y1)-(x2,y2) eg.
            ---
            MOVE (  0.000,  0.000)-( 50.000, 33.333)  Values line up vertically
            DRAW ( 50.000, 33.333)-(100.000, 50.000)
            DRAW (100.000, 50.000)-( 50.000, 66.667)
            ---
            DRAW ( 50.000, 66.667)-( 50.000, 33.333)

    MAKE_FILE_TARGETS
        EXEC = TurtleGraphics
        EXEC_S = TurtleGraphicsSimple (Black and White)
        EXEC_D = TurtleGraphicsDebug (-Print log file entries as well as file
                                      -Every call to line() should be followed by a log
                                     )
    
    4.REPORT: Outline design and testing
        1. For each function
            -Decribe its purpose (1 para)
        2. On coverting the input file to a coordinate system
            -Describe implementation (2-3 para)
            -Describe an alternative approach (1-2 para)
        3. Demonstrate with sample input and output
            -Command-line for execute
            -User input via terminal
            -Contents of input file
            -Output as shown on screen
        4. INCLUDE CONTENTS PAGE AND PAGE NUMBERS

    5.SUBMISSION
        YOU CAN WORRY ABOUT THIS SOME OTHER TIME LIL NIGGA!!!!