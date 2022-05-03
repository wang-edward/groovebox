#include "plot.hpp"

plot:: plot() {
    //TODO remove?
}

void plot:: init() {
    tex.create2D(t_width, t_height, al::Texture::RGBA8, al::Texture::RGBA, al::Texture::UBYTE);
    tex.filterMag(al::Texture::NEAREST); // magnification filter is nearest-neighbour interpolation
    
    stride = tex.numComponents();

    pixels.resize(stride * t_width * t_height);

    //setup mesh
    mesh.primitive(al::Mesh::TRIANGLE_STRIP);
    mesh.vertex(-1, 1);
    mesh.vertex(-1, -1);
    mesh.vertex(1, 1);
    mesh.vertex(1, -1);

    // Add texture coordinates
    mesh.texCoord(0, 1);
    mesh.texCoord(0, 0);
    mesh.texCoord(1, 1);
    mesh.texCoord(1, 0);
}

// IDEA pass a reference to Graphics& g and plot& p
// use g to do global graphics stuff if needed
// actually draw to p
// then use plot::render(g) to actually draw at the end
// TEX.SUBMIT SHOULD ONLY HAPPEN ONCE PER CYCLE

void plot:: render(al::Graphics& g) {
    g.camera(al::Viewpoint::IDENTITY);  
    al::Color col = al::HSV(1, 1, 1);

    // circle(20,20, 20, col);

    tex.submit(pixels.data());
    tex.bind();
    g.texture();
    g.draw(mesh);
    tex.unbind();

    reset_buffer();
}


void plot:: plot_pixel(al::Color c, int x, int y) {
    int idx = y * t_width + x;

    pixels[idx * stride + 0] = c.r * 255.;
    pixels[idx * stride + 1] = c.g * 255.;
    pixels[idx * stride + 2] = c.b * 255.;
    pixels[idx * stride + 3] = c.a;
}

void plot:: circle (int x_center, int y_center, int radius, al::Color c) {
    int x = 0; 
    int y = radius;
    int p = (5-radius * 4)/4;

    circle_points(x_center, y_center, x, y, c);
    while (x < y) {
        x++;
        if (p<0) {
            p+=2*x + 1;
        } else {
            y--;
            p += 2*(x-y) + 1;
        }
        circle_points(x_center, y_center, x, y, c);
    }

}

void plot:: circle_points(int cx, int cy, int x, int y, al::Color pix) {
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

//try to avoid
void plot:: reset_buffer() {
    std::fill(pixels.begin(), pixels.end(), 0);
}

void plot:: draw_image(int x_position, int y_position, al::Image image) {
    int position = y_position * t_width + x_position;
    for (int y=0;y<image.height();y++) {
        for (int x=0;x<image.width();x++) {
            int idx = ((x * 4) + y) * 4; //stride = 4
            al::Color c (image.array()[idx]/255., image.array()[idx+1]/255., image.array()[idx+2]/255., image.array()[idx+3]/255.);

            plot_pixel(c, x_position + x, y_position + y);
        }
    }
    
    // vector_copy(image.array(), pixels, position);
}

//where v1 is bigger than v2, copy v2 into v1
// source, destination, position
void plot:: vector_copy(std::vector<uint8_t> &v2, std::vector<uint8_t> &v1, int pos) {
    if (v2.size() + pos > v1.size()) {
        // std::cout<<v1.size()<<" "<<v2.size()<<" "<<pos<<" overage"<<std::endl;
        return;
    } else {
        // std::cout<<"not over"<<std::endl;
    }
    copy(v2.begin(), v2.end(), v1.begin() + pos);
}
