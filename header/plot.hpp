#ifndef PLOT_HPP
#define PLOT_HPP

#include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Texture.hpp"
#include "al/graphics/al_Graphics.hpp"
#include "al/graphics/al_Image.hpp"
#include <vector>
#include <cstdint>
#include <algorithm> 
#include <iterator>

class plot  {

  public:
    plot();
    void init();
    void render(al::Graphics& g);
    void reset_buffer();
    void plot_pixel(al::Color c, int x, int y);

  protected:
    const int t_width = 240;
    const int t_height = 160;
    al::Texture tex;
    al::Mesh mesh;
    int stride;
    std::vector<uint8_t> pixels;
};

#endif