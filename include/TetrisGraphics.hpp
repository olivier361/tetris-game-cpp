#ifndef TETRIS_GRAPHICS_HPP
#define TETRIS_GRAPHICS_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include "DrawableObject.hpp"
#include "../src/Config.hpp"

namespace Graphics {

    class TetrisGraphics {

        /// PRIVATE STATIC VARIABLES ///

        private:

        static int timeAtLastFPSMesure; // the time (in milliseconds) since program was launched. Updated after each time the FPS is recomputed.
        static int framesDrawnInLastSecond; // a count of how many frames were rendered in the last second.
        static int curFPS; // the current average FPS value for the within the last second.

        /// PRIVATE VARIABLES ///

        //Define RGBA values for Tetris block colors.
        static const double sColorRed[4];
        static const double sColorGreen[4];
        static const double sColorBlue[4];
        static const double sColorOrange[4];
        static const double sColorPurple[4];
        static const double sColorYellow[4];
        static const double sColorCyan[4];
        static const double sColorGray[4];

        static const double sColorRedOutline[4];
        static const double sColorGreenOutline[4];
        static const double sColorBlueOutline[4];
        static const double sColorOrangeOutline[4];
        static const double sColorPurpleOutline[4];
        static const double sColorYellowOutline[4];
        static const double sColorCyanOutline[4];
        static const double sColorGrayOutline[4];

        // const double mColorRed[4] = {1.0, 0.0, 0.0, 1.0};       // #FF0000 Red
        // const double mColorGreen[4] = {0.0, 1.0, 0.0, 1.0};     // #00FF00 Green
        // const double mColorBlue[4] = {0.0, 0.0, 1.0, 1.0};      // #0000FF Blue
        // const double mColorOrange[4] = {1.0, 0.5, 0.0, 1.0};    // #FF7F00 Orange
        // const double mColorPurple[4] = {0.5, 0.0, 0.5, 1.0};    // #800080 Purple
        // const double mColorYellow[4] = {1.0, 1.0, 0.0, 1.0};    // #FFFF00 Yellow
        // const double mColorCyan[4] = {0.0, 1.0, 1.0, 1.0};      // #00FFFF Cyan
        // const double mColorGray[4] = {0.42, 0.42, 0.42, 1.0};   // #6D6D6D Gray

        // const double mColorRedOutline[4] = {0.76, 0.0, 0.0, 1.0};       // #C30000 Dark Red
        // const double mColorGreenOutline[4] = {0.0, 0.76, 0.0, 1.0};     // #00C300 Dark Green
        // const double mColorBlueOutline[4] = {0.0, 0.0, 0.72, 1.0};      // #0000B9 Dark Blue
        // const double mColorOrangeOutline[4] = {0.86, 0.43, 0.0, 1.0};   // #DC6D00 Dark Orange
        // const double mColorPurpleOutline[4] = {0.34, 0.0, 0.34, 1.0};   // #570057 Dark Purple
        // const double mColorYellowOutline[4] = {0.8, 0.8, 0.0, 1.0};     // #CBCB00 Dark Yellow
        // const double mColorCyanOutline[4] = {0.0, 0.68, 0.68, 1.0};     // #00ADAD Dark Cyan
        // const double mColorGrayOutline[4] = {0.25, 0.25, 0.25, 1.0};    // #404040 Dark Gray


        /// CONSTRUCTORS ///

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
        static void drawSquare(double tlx, double tly, double brx, double bry, const double rgba[4]);

        /// @brief Renders the outline of a square on-screen
        ///        given the top-left and bottom-right coordinates
        ///        of the square, the lineWidth and the color.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param brx: bottom-right x coordinate.
        /// @param bry: bottom-right y coordinate.
        /// @param lineWidth: the width in pixels of the outline.
        /// @param rgba: the color for drawing the square.
        static void drawSquareOutline(double tlx, double tly, double brx, double bry, double lineWidth, const double rgba[4]);

        /// @brief Renders a Tetris block of the given Config::BlockColor
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param blockColor: the Config::BlockColor for drawing the block.
        static void drawBlock(double tlx, double tly, const Config::BlockColor blockColor);

        /// @brief Displays the given string on-screen with the Helvetica 18 text being
        ///        left justified starting at the given coordinates.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param rgba: the color for drawing the text. 
        /// @param text: the string to render.
        static void drawText(double tlx, double tly, const double rgba[4], const char text[]);

        /// @brief Displays the given string on-screen with the Times Roman 24 text being
        ///        left justified starting at the given coordinates.
        /// @param tlx: top-left x coordinate.
        /// @param tly: top-left y coordinate.
        /// @param rgba: the color for drawing the text. 
        /// @param text: the string to render.
        static void drawHeader(double tlx, double tly, const double rgba[4], const char text[]);

        // TODO: Write graphics methods to draw things


        /// HELPER FUNCTIONS ///

        private:

        static void displayUpdate();

    }; // End of TetrisGraphics class.


} // End of Graphics namespace.


#endif