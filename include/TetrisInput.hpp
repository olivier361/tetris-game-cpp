#ifndef TETRIS_INPUT_HPP
#define TETRIS_INPUT_HPP

// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <GL/glut.h>
#include <GL/freeglut.h>
#include "../src/Config.hpp"
#include "../src/Playfield.hpp"

namespace Input {

    class TetrisInput {

        /// STATIC MEMBER VARIABLES ///

        public:

        static Playfield* sPlayfield; // A pointer to the Playfield object that constrols the game.

        /// CONSTRUCTORS ///

        TetrisInput() = delete;

        TetrisInput(Playfield* playfield);


        /// MEMBER FUNCTIONS ///

        // TODO: Delete. These GLUT callback function seemingly cannot be member functions.
        // The function called by GLUT to process ASCII key presses.
        //void processNormalKeys(unsigned char key, int x, int y);


    }; // End of TetrisInput class.

} // End of Input namespace.

#endif