#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "header/plot.hpp"
#include "al/types/al_Color.hpp"

class shape : protected plot{

    public:
        void set_position(int x, int y);
        virtual void render (plot& p);

    protected:
        int x_position;
        int y_position;
        al::Color color;
};

#endif