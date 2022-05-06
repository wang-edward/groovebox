#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "header/shape.hpp"

class circle : shape {
    int radius;

    void render (plot& p) override;
    void draw_circle(int x_center, int y_center, int radius, al::Color c);
    void draw_circle_points(int cx, int cy, int x, int y, al::Color pix);
};

#endif