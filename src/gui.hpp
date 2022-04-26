#ifndef GUI_HPP
#define GUI_HPP

#include "al/graphics/al_Graphics.hpp"
// #include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Shapes.hpp"
// #include "al/graphics/al_"
#include "al/io/al_Window.hpp"
#include "al/types/al_Color.hpp"
#include <random>
#include <math.h>


class gui {
    
    public:
        void init();
        void render (al::Graphics& g);
        void update_scaling(float x, float y);
        void rand_color(); //TODO remove

    protected:
        al::EasyFBO fbo;
        al::Mesh frame;
        al::Mesh grid;

        static const int x_dimension = 240;
        static const int y_dimension = 160;

        float x_scaling = 1;
        float y_scaling = 1;

        al::Mesh test [x_dimension][y_dimension];
};

#endif