#ifndef GUI_HPP
#define GUI_HPP

#include "al/graphics/al_Graphics.hpp"
// #include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Shapes.hpp"
// #include "al/graphics/al_"
#include "al/io/al_Window.hpp"


class gui {
    
    public:
        void init();
        void render (al::Graphics& g);

    protected:
        al::EasyFBO fbo;
        al::Mesh frame;
};

#endif