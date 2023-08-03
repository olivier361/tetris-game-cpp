#include "Graphics.hpp"

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

void Graphics::TetrisGraphics::displayLoop() {
    glutDisplayFunc(displayUpdate);
    glClearColor(0.2, 0.3, 1.0, 1.0);
    glutMainLoop();
}

void Graphics::TetrisGraphics::displayUpdate() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw stuff here
    // std::cout << "inside display\n";

    // updateTriangle(0.0, -0.0005);

    // does not work
    // set_colour(1.0, 0.0, 0.0); // dark blue

    glColor3f(1.0, 0.0, 0.0);

    // use GL_POLYGON to make a square potentially (or just two triangles)
	glBegin(GL_TRIANGLES);
		// glVertex2d(-0.5, 0.5);
        // glVertex2d(0.5, 0.5);
        // glVertex2d(0.0, -0.5);

        glVertex2d(-0.5, 0.5);
        glVertex2d(0.5, 0.5);
        glVertex2d(0.0, -0.5);
	glEnd();

    glRasterPos2i(0, -0.5);
    // glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glColor3f(0.0, 1.0, 0.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Sample Text: 1000");
    
    glFlush();
    glutPostRedisplay();
}



