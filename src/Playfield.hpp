#ifndef PLAYFIELD_HPP
#define PLAYFIELD_HPP

#include "Config.hpp"
#include "DrawableObject.hpp"
#include "Tetromino.hpp"

class Playfield : public Graphics::DrawableObject {

    /// MEMBER VARIABLES ///

    private:

    // The matrix that keeps track of what blocks are currently on the playing grid.
    Config::BlockColor mMatrix[Config::playfieldBlockHeight][Config::playfieldBlockWidth];

    Tetromino mTetrominoManager; // The Tetromino object associated with this Playfield instance.

    int mOffsetX; // The X pixel coordinate offset for the top-right corner of the playfield object.
    int mOffsetY; // The Y pixel coordinate offset for the top-right corner of the playfield object.

    int mScore;         // Keeps track of the current score.
    int mHighScore;     // Keeps track of the highest recorded score since the program was launched.
    int mLinesCleared;  // Keeps track of the total amount of lines cleared in the current game.


    /// CONSTRUCTORS ///

    public:

    // Constructor creates a Playfield object which is drawn
    // with the top left corner of the grid at the given coordinates.
    Playfield(int xPos = 0, int yPos = 0);


    /// MEMBER FUNCTIONS ///

    // overload the display function from DrawableObject
    // to define how the Playfield is to be drawn on screen.
    void display();

    /// HELPER FUNCTIONS ///




}; // End of Playfield class.

#endif