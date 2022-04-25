#include "gui.hpp"

#include <iostream> //TODO remove

void gui::init () {

    // std::cout<<<<std::endl;

    al::addWireBox(frame, 4.0f, (8.0/3.0), 0.1f);
}

void gui:: render (al::Graphics& g) {
    g.draw(frame);
}