#ifndef TETRIS_INPUT_HPP
#define TETRIS_INPUT_HPP

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


        /// STATIC MEMBER FUNCTIONS ///

        // Calls the game timer used to make Tetrominos fall
        // with the given millisecond parameter.
        static void callGameTimer(int ms);

    }; // End of TetrisInput class.

} // End of Input namespace.

#endif