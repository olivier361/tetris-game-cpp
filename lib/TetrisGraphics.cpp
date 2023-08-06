#include <cstdio>
#include "TetrisGraphics.hpp"
#include "../src/Config.hpp"

Graphics::TetrisGraphics::TetrisGraphics(int xSize, int ySize, const char* windowName) {
    
    // Initialize GLUT.
    // glutInit(&argc, argv); // call in main to as arguments need to be passed according to documentation.
    glutInitDisplayMode(GLUT_RGB);

    // Initially open the window with a slight offset from
    // the top left corner of the screen. The user can still
    // move the windows as desired however.
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(xSize, ySize);
    glutCreateWindow(windowName);
}


/// MEMBER FUNCTIONS ///

void Graphics::TetrisGraphics::displayLoop() {
    glutDisplayFunc(displayUpdate);
    glClearColor(0.43, 0.59, 1.0, 1.0); // light pastel blue.
    glutMainLoop();
}


/// STATIC VARIABLE INITIALIZATION ///

std::vector<Graphics::DrawableObject *> Graphics::TetrisGraphics::sDrawableObjectList;

int Graphics::TetrisGraphics::timeAtLastFPSMesure;
int Graphics::TetrisGraphics::framesDrawnInLastSecond;
int Graphics::TetrisGraphics::curFPS;


/// STATIC FUNCTIONS ///

/// @brief Renders a filled-in square on-screen
///        given the top-left and bottom-right coordinates
///        of the square and the color.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param brx: bottom-right x coordinate.
/// @param bry: bottom-right y coordinate.
/// @param rgba: the color for drawing the square.
void Graphics::TetrisGraphics::drawSquare(double tlx, double tly, double brx, double bry, const double rgba[4]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glBegin(GL_QUADS);
        glVertex2d(tlx, tly);
        glVertex2d(brx, tly);
        glVertex2d(brx, bry);
        glVertex2d(tlx, bry);
    glEnd();
}

/// @brief Renders the outline of a square on-screen
///        given the top-left and bottom-right coordinates
///        of the square, the lineWidth and the color.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param brx: bottom-right x coordinate.
/// @param bry: bottom-right y coordinate.
/// @param lineWidth: the width in pixels of the outline.
/// @param rgba: the color for drawing the square.
void Graphics::TetrisGraphics::drawSquareOutline(double tlx, double tly, double brx, double bry, double lineWidth, const double rgba[4]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
        glVertex2d(tlx, tly);
        glVertex2d(brx, tly);
        glVertex2d(brx, bry);
        glVertex2d(tlx, bry);
    glEnd();
}

/// @brief Displays the given string on-screen with the Helvetica 18 text being
///        left justified starting at the given coordinates.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param rgba: the color for drawing the text. 
/// @param text: the string to render.
void Graphics::TetrisGraphics::drawText(double tlx, double tly, const double rgba[4], const char text[]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glRasterPos2d(tlx, tly);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);
}

/// @brief Displays the given string on-screen with the Times Roman 24 text being
///        left justified starting at the given coordinates.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param rgba: the color for drawing the text. 
/// @param text: the string to render.
void Graphics::TetrisGraphics::drawHeader(double tlx, double tly, const double rgba[4], const char text[]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glRasterPos2d(tlx, tly);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text);
}

/// HELPER FUNCTIONS ///

void Graphics::TetrisGraphics::displayUpdate() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // This makes sets the viewport to be of a fixed size no matter
    // if the window shape is rezised by the user.
    // Doing so avoids rendered shapes to be squished/stretched when
    // changing the window's aspect ratio.
    glViewport(0, 0, Config::windowSizeX, Config::windowSizeY);

    // Transforms the coordinates used to render shapes from relative coordinates
    // (-1.0 <= x <= 1.0, -1.0 <= y <= 1.0) to using exact pixel coordinates
    // (0 <= x <= 1279, 0 <= y <= 719).
    glOrtho(0.0, Config::windowSizeX, Config::windowSizeY, 0.0, 0.0, 1.0);

    // draw stuff here
    // std::cout << "inside display\n";

    // updateTriangle(0.0, -0.0005);

    // does not work
    // set_colour(1.0, 0.0, 0.0); // dark blue

    // glColor3f(1.0, 0.0, 0.0);

    // // use GL_POLYGON to make a square potentially (or just two triangles)
	// glBegin(GL_TRIANGLES);
	// 	// glVertex2d(-0.5, 0.5);
    //     // glVertex2d(0.5, 0.5);
    //     // glVertex2d(0.0, -0.5);

    //     glVertex2d(-0.5, 0.5);
    //     glVertex2d(0.5, 0.5);
    //     glVertex2d(0.0, -0.5);
	// glEnd();

    // Call the display function of each registered DrawableObject.
    for (std::size_t i = 0; i < sDrawableObjectList.size(); ++i) {
        sDrawableObjectList[i]->display();
    }

    glColor3f(0.0, 1.0, 0.0);
    // glRasterPos2i(0, -0.5);
    glRasterPos2d(0.0, -0.5);
    // glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Sample Text: 1000");
    

    // Compute and display framerate:

    if (Config::displayFPS) {
        ++framesDrawnInLastSecond;

        int timeSinceBoot = glutGet(GLUT_ELAPSED_TIME);

        // compute average fps in the last second of runtime.
        if (timeSinceBoot - timeAtLastFPSMesure >= 1000) {
            curFPS = (int) (framesDrawnInLastSecond * (1000.0 / (double)(timeSinceBoot - timeAtLastFPSMesure)));
            framesDrawnInLastSecond = 0;
            timeAtLastFPSMesure = timeSinceBoot;
        }

        // display the FPS string on-screen.
        char fpsString[128];
        sprintf(fpsString,"AVG FPS: %4d", curFPS);

        glColor3f(0.0, 0.0, 1.0);
        glRasterPos2d(10, Config::windowSizeY - 10);
        glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)fpsString);
    }

    // flush buffer to and call function again to render next frame.
    glFlush();
    glutPostRedisplay();
}



