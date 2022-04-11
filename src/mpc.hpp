#ifndef MPC_HPP
#define MPC_HPP
#include "sample.hpp"
#include <string>
#include <filesystem>
#include "al/graphics/al_Graphics.hpp"

class mpc  {

  public:
    const int NUMBER_VOICES = 12;
    sample samples[16];
    void init();
    void init_files();
    void position_discs();
    void color_discs();
    void draw(al::Graphics &g);
    float output();
    void key_down(int key);
};

#endif