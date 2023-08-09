#include "OverlayManager.hpp"
#include "TetrisGraphics.hpp"

/// HELPER FUNCTIONS ///

// Draws an overlay in the middle of the screen with the given string.
void drawOverlay(int textOffset, const char text[]) {
    const int boxHalfWidth = 105;
    const int boxHalfHeight = 45;
    const int borderWidth = 4;
    const double red[4] = {1.0, 0.0, 0.0, 1.0}; // #FF0000 Red
    const double black[4] = {0.0, 0.0, 0.0, 1.0}; // #000000 Black

    Graphics::TetrisGraphics::drawSquare(
        (Config::windowSizeX / 2) - boxHalfWidth,
        (Config::windowSizeY / 2) - boxHalfHeight,
        (Config::windowSizeX / 2) + boxHalfWidth,
        (Config::windowSizeY / 2) + boxHalfHeight,
        red);

    Graphics::TetrisGraphics::drawSquare(
        (Config::windowSizeX / 2) - boxHalfWidth + borderWidth,
        (Config::windowSizeY / 2) - boxHalfHeight + borderWidth,
        (Config::windowSizeX / 2) + boxHalfWidth - borderWidth,
        (Config::windowSizeY / 2) + boxHalfHeight - borderWidth,
        black);

    Graphics::TetrisGraphics::drawText(
        (Config::windowSizeX / 2) - boxHalfWidth + textOffset,
        (Config::windowSizeY / 2) - 5,
        red,
        text);
}

/// CONSTRUCTORS ///

// Constructs an OverlayManager which displays overlays
// based on the state of its SetOverlay variables.
OverlayManager::OverlayManager() {
    mSetPauseOverlay = false;
    mSetGameOverOverlay = false;
}


/// MEMBER FUNCTIONS ///

// overload the display function from DrawableObject
// to define how the active block is to be drawn on screen.
void OverlayManager::display() {
    if (mSetPauseOverlay) {
        drawPauseOverlay();
    }
    if (mSetGameOverOverlay) {
        drawGameOverOverlay();
    }
}

// Draws a Pause message overlay in the middle of the screen.
void OverlayManager::drawPauseOverlay() {
    drawOverlay(25, "   GAME PAUSED\nPress 'P' to resume.");
}

// Draws a Game Over message overlay in the middle of the screen.
void OverlayManager::drawGameOverOverlay() {
    drawOverlay(15, "    GAME OVER\nPress 'N' to play again.");
}
