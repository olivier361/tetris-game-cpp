#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

namespace Graphics {

    // NOTE: Any class that wishes to be able to draw something
    // in the graphics window should inherit the DrawableObject class
    // and implement the virtual function display().

    class DrawableObject {

        public:

        DrawableObject() {};

        // a virtual method that must be implemented by the inheriting class.
        // This function determines what is drawn on screen for the inheriting object.
        virtual void display() {};

    }; // End of DrawableObject class.

} // End of Graphics namespace.

#endif