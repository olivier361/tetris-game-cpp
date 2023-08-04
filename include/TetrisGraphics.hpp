#ifndef TETRIS_GRAPHICS_HPP
#define TETRIS_GRAPHICS_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

namespace Graphics {

    class TetrisGraphics {

        public:

        // The graphics window is not default constructible.
        TetrisGraphics() = delete;

        // Constructor sets up graphics window with the provided x,y size and initializes everything.
        TetrisGraphics(int xSize, int ySize, const char* windowName = "My Program");

        /// MEMBER FUNCTIONS ///

        void displayLoop();

        /// HELPER FUNCTIONS

        private:

        static void displayUpdate();


    }; // End of TetrisGraphics class.


} // End of Graphics namespace.


#endif