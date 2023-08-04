#include <iostream>
#include <string>
#include "Config.hpp"
#include "TetrisGraphics.hpp"
#include "Playfield.hpp"

// NOTE: This is the entry point for the program.

int main(int argc, char** argv) {
    std::cout << "Launching game...\n";

    // TODO: Launch game loop.

    glutInit(&argc, argv);
    Graphics::TetrisGraphics window(Config::windowSizeX, Config::windowSizeY, Config::appName);


    Playfield* gameMatrix = new Playfield(); // TODO: set playfield to correct position

    // Add objects we want rendered to the sDrawableObjectList.
    window.sDrawableObjectList.push_back(gameMatrix);

    window.displayLoop();
    
    // TODO: Delete memory for gameMatrix to avoid memory leaks

    std::cout << "graphics window created!\n";

    // TODO: Implement GlutCloseFunc somewhere. Runs code as the windows is closed with X. Do cleanup steps.
    
    return 0;
}