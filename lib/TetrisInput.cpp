#include "TetrisInput.hpp"

/// HELPER FUNCTION DECLARATIONS ///

void processNormalKeys(unsigned char key, int x, int y);


/// CONSTRUCTORS ///

Input::TetrisInput::TetrisInput(Playfield* playfield) {

    sPlayfield = playfield;

    // Setup function to call on ASCII key presses.
    glutKeyboardFunc(processNormalKeys);
}

/// STATIC VARIABLE INITIALIZATION ///

Playfield* Input::TetrisInput::sPlayfield;


/// MEMBER FUNCTIONS ///

// The function called by GLUT to process ASCII key presses.
void processNormalKeys(unsigned char key, int x, int y) {

    // TODO: implement.

    if (key == 65 || key == 97) { // A || a
        Input::TetrisInput::sPlayfield->moveLeft();
    }
    else if (key == 68 || key == 100) { // D || d
        Input::TetrisInput::sPlayfield->moveRight();
    }
}
