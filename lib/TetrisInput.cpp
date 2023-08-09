#include "TetrisInput.hpp"

/// HELPER FUNCTION DECLARATIONS ///

void onDropTimerWrapper(int value);
void processNormalKeys(unsigned char key, int x, int y);


/// CONSTRUCTORS ///

Input::TetrisInput::TetrisInput(Playfield* playfield) {

    sPlayfield = playfield;

    // Setup function to call on ASCII key presses.
    glutKeyboardFunc(processNormalKeys);
}

/// STATIC VARIABLE INITIALIZATION ///

Playfield* Input::TetrisInput::sPlayfield;


/// STATIC MEMBER FUNCTIONS ///

// Call the game timer used to make Tetrominos fall
// with the given millisecond parameter.
void Input::TetrisInput::callGameTimer(int ms) {
    if (!sPlayfield->mIsNextDropScheduled) {
        sPlayfield->mIsNextDropScheduled = true;
        glutTimerFunc(ms, onDropTimerWrapper, 0);
    }
}


/// HELPER FUNCTIONS ///

// Wraps the call to Playfields OnDropTimer() member function
// since the glutTimerFunc only accepts non-member functions.
void onDropTimerWrapper(int value) {
    Input::TetrisInput::sPlayfield->onDropTimer(value);
}

// The function called by GLUT to process ASCII key presses.
void processNormalKeys(unsigned char key, int x, int y) {

    // TODO: implement.

    if (key == 32) { // SPACEBAR
        Input::TetrisInput::sPlayfield->hardDrop();
    }
    else if (key == 65 || key == 97) { // A || a
        Input::TetrisInput::sPlayfield->moveLeft();
    }
    else if (key == 68 || key == 100) { // D || d
        Input::TetrisInput::sPlayfield->moveRight();
    }
    else if (key == 78 || key == 110) { // N || n
        Input::TetrisInput::sPlayfield->startGame();
    }
    else if (key == 80 || key == 112) { // P || p
        Input::TetrisInput::sPlayfield->pauseToggle();
    }
}
