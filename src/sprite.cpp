#include "header/sprite.hpp"

int sprite:: get_image_index (int x, int y, al::Image image) {
    return ((y * image.width()) + x) * 4; //stride = 4
}

void sprite:: draw_image(int x_position, int y_position, al::Image image, plot& p) {

    if (image.width() > plot::width || image.height() > plot::height) {
        std::cout<<"ImAGE TOO BIG!"<<std::endl;;
        return;
    }   

    x_position = x_position + (image.width())/2;
    y_position = y_position + (image.height())/2;

    int position = x_position * plot::width + y_position;
    for (int y=image.height()-1;y>=0;y--) {
        for (int x=image.width()-1;x>=0;x--) {

            int red = get_image_index(x, y, image);
            int green = red + 1;
            int blue = red + 2;
            int a = red + 3;

            if (a!=0) {
                al::Color c (image.array()[red]/255., image.array()[green]/255., image.array()[blue]/255., image.array()[a]/255.);
                p.plot_pixel(c, x_position - x, y_position - y);
            }
        }
    }
}