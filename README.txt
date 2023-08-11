Classic Tetris Game in C++ | SENG 475: project
created by Olivier Gervais-Gougeon

[ ABOUT THE PROGRAM: ]

This is a classic game of Tetris built using C++ with OpenGL and freeglut.

The goal of the game is for the player to move and rotate the falling blocks
in order to fill horizontal lines on the play grid. When a line is filled,
the player is awarded some points and the line is cleared making the lines above
shift down a row. The goal is to get the highest score while avoiding that a block
reaches the top most row of the play grid. Doing so results in a game over.


[ BUILDING & INSTALLING THE SOFTWARE: ]

The software can be built by following the instructions below:

Let $TOP_DIR denote the directory containing this README file
(i.e. the top level of the repository).
Let $INSTALL_DIR denote the directory into which the user wishes the software to be installed.

To build and install the software, use the commands:
    cd $TOP_DIR
    cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
    cmake --build tmp_cmake --clean-first --target install

The installed software will now be located in '$INSTALL_DIR/bin'.


[ RUNNING THE SOFTWARE: ]

Along with the installed software is a demo script that can be used to launch the software.
The demo script can be run as seen below:

    $INSTALL_DIR/bin/demo

Since the demo script simply launches the Tetris program,
the game can also be launched directly. The result will be the same.

    $INSTALL_DIR/bin/tetris

NOTE: The software does not support any command line parameters or input/output files
as all user interactions happen within the graphical user interface.


[ GAME CONTROLS: ]

The game can be played using the following keyboard controls.

IMPORTANT: Note that the 'N' key must be pressed to start a new round of Tetris.
A new game can be started with the 'N' key at any time (during a running game or a game over).

    - N: Start a new game
    - P: Pause game
    - ESC: Exit game
    - W: Rotate block clockwise
    - Q: Rotate block counterclockwise
    - A: Move block left
    - D: Move block right
    - Space: “Hard drop” the active block
