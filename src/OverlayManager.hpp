#ifndef OVERLAY_MANAGER_HPP
#define OVERLAY_MANAGER_HPP

#include "Config.hpp"
#include "DrawableObject.hpp"

class OverlayManager : public Graphics::DrawableObject {
    
    /// MEMBER VARIABLES ///
    
    public:

    bool mSetPauseOverlay;
    bool mSetGameOverOverlay;

    /// CONSTRUCTORS ///

    // Constructs an OverlayManager which displays overlays
    // based on the state of its SetOverlay variables.
    OverlayManager();

    /// MEMBER FUNCTIONS ///

    // overload the display function from DrawableObject
    // to define how the active block is to be drawn on screen.
    void display();

    // Draws a Pause message overlay in the middle of the screen.
    void drawPauseOverlay();

    // Draws a Game Over message overlay in the middle of the screen.
    void drawGameOverOverlay();

}; // End of OverlayManager class.

#endif