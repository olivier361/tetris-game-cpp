#include "TetrisGraphics.hpp"

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


/// STATIC VARIABLES ///

std::vector<Graphics::DrawableObject *> Graphics::TetrisGraphics::sDrawableObjectList;


/// STATIC FUNCTIONS ///

/// @brief Renders a filled-in square on-screen
///        given the top-left and bottom-right coordinates
///        of the square and the color.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param brx: bottom-right x coordinate.
/// @param bry: bottom-right y coordinate.
/// @param rgba: the color for drawing the square.
void Graphics::TetrisGraphics::drawSquare(double tlx, double tly, double brx, double bry, double rgba[4]) {
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
void Graphics::TetrisGraphics::drawSquareOutline(double tlx, double tly, double brx, double bry, double lineWidth, double rgba[4]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
        glVertex2d(tlx, tly);
        glVertex2d(brx, tly);
        glVertex2d(brx, bry);
        glVertex2d(tlx, bry);
    glEnd();
}

/// @brief Displays the given string on-screen with the text being
///        left justified starting at the given coordinates.
/// @param tlx: top-left x coordinate.
/// @param tly: top-left y coordinate.
/// @param rgba: the color for drawing the text. 
/// @param text: the string to render.
void Graphics::TetrisGraphics::drawText(double tlx, double tly, double rgba[4], const char text[]) {
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glRasterPos2d(tlx, tly);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);
}


/// HELPER FUNCTIONS ///

void Graphics::TetrisGraphics::displayUpdate() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

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
    
    glFlush();
    glutPostRedisplay();
}



