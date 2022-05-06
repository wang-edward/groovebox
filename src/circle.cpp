#include "header/circle.hpp"

void circle:: render (plot& p) {
    std::cout<<"test"; // TODO override circle render
}

void circle:: draw_circle (int x_center, int y_center, int radius, al::Color c) {
    int x = 0; 
    int y = radius;
    int p = (5-radius * 4)/4;

    draw_circle_points(x_center, y_center, x, y, c);
    while (x < y) {
        x++;
        if (p<0) {
            p+=2*x + 1;
        } else {
            y--;
            p += 2*(x-y) + 1;
        }
        draw_circle_points(x_center, y_center, x, y, c);
    }

}

void circle:: draw_circle_points(int cx, int cy, int x, int y, al::Color pix) {
    if (x==0) {
      plot_pixel(pix, cx, cy + y);
      plot_pixel(pix, cx, cy - y);
      plot_pixel(pix, cx + y, cy);
      plot_pixel(pix, cx - y, cy);
    } else if (x == y) {
      plot_pixel(pix, cx + x, cy + y);
      plot_pixel(pix, cx - x, cy + y);
      plot_pixel(pix, cx + x, cy - y);
      plot_pixel(pix, cx - x, cy - y);
    } else if (x < y) {
      plot_pixel(pix, cx + x, cy + y);
      plot_pixel(pix, cx - x, cy + y);
      plot_pixel(pix, cx + x, cy - y);
      plot_pixel(pix, cx - x, cy - y);

      plot_pixel(pix, cx + y, cy + x);
      plot_pixel(pix, cx - y, cy + x);
      plot_pixel(pix, cx + y, cy - x);
      plot_pixel(pix, cx - y, cy - x);
    }
}