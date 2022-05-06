#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "al/graphics/al_Mesh.hpp"
#include "al/graphics/al_Image.hpp"
#include <vector>
#include <cstdint>
#include <algorithm> 
#include <iterator>

class plot  {

  public:
    void init();
    void render(plot& p) override;

    void draw_image(int x_position, int y_position, al::Image image);

    int get_image_index (int x, int y, al::Image image);

  protected:
};

#endif