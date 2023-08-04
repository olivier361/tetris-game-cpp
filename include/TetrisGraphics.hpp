#ifndef TETRIS_GRAPHICS_HPP
#define TETRIS_GRAPHICS_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include "DrawableObject.hpp"

namespace Graphics {

    class TetrisGraphics {

        public:

        // The graphics window is not default constructible.
        TetrisGraphics() = delete;

        // Constructor sets up graphics window with the provided x,y size and initializes everything.
        TetrisGraphics(int xSize, int ySize, const char* windowName = "My Program");

        /// MEMBER FUNCTIONS ///

        void displayLoop();

        /// STATIC VARIABLES ///

        static std::vector<Graphics::DrawableObject *> sDrawableObjectList;

        /// STATIC FUNCTIONS ///

        /// @brief Renders a filled-in square on-screen
        ///        given the top-left and bottom-right coordinates
        ///        of the square and the color.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param brx: bottom-right x coordinate.
        /// @param bry: bottom-right y coordinate.
        /// @param rgba: the color for drawing the square.
        static void drawSquare(double tlx, double tly, double brx, double bry, double rgba[4]);

        /// @brief Renders the outline of a square on-screen
        ///        given the top-left and bottom-right coordinates
        ///        of the square, the lineWidth and the color.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param brx: bottom-right x coordinate.
        /// @param bry: bottom-right y coordinate.
        /// @param lineWidth: the width in pixels of the outline.
        /// @param rgba: the color for drawing the square.
        static void drawSquareOutline(double tlx, double tly, double brx, double bry, double lineWidth, double rgba[4]);

        /// @brief Displays the given string on-screen with the text being
        ///        left justified starting at the given coordinates.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param rgba: the color for drawing the text. 
        /// @param text: the string to render.
        static void drawText(double tlx, double tly, double rgba[4], const char text[]);

        // TODO: Write graphics methods to draw things


        /// HELPER FUNCTIONS ///

        private:

        static void displayUpdate();

    }; // End of TetrisGraphics class.


} // End of Graphics namespace.


#endif