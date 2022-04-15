#ifndef MPC_HPP
#define MPC_HPP
#include "sample.hpp"
#include <string>
#include <filesystem>
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Font.hpp"

class mpc  {

  public:
    static const int NUMBER_SAMPLES = 12;
    sample samples[NUMBER_SAMPLES];
    al::Font font;
    al::Mesh text;
    void init();
    void init_font();
    void init_files();
    void color_discs();
    void position_discs();
    void draw(al::Graphics &g);
    void draw_gui(al::Graphics &g);
    float output();
    void key_down(int key);
};

#endif