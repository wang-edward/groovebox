#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "header/plot.hpp"

class circle {

    public:

        circle(int x, int y, int radius);
        void draw(al::Color c, plot& p);
        void draw_circle(int x_center, int y_center, int radius, al::Color c, plot& p);
        void draw_circle_points(int cx, int cy, int x, int y, al::Color pix, plot& p);

    protected:
        int x_position;
        int y_position;
        int radius;

};

#endif