#ifndef PLAYFIELD_HPP
#define PLAYFIELD_HPP

#include "Config.hpp"
#include "DrawableObject.hpp"

class Playfield : public Graphics::DrawableObject {

    /// MEMBER VARIABLES ///

    private:

    Config::BlockColors mMatrix[Config::playfieldBlockHeight][Config::playfieldBlockWidth];

    int mScore;
    int mHighScore;
    int mLinesCleared;


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