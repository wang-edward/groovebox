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
    // mesh.texCoord(1, 0);
    // mesh.texCoord(1, 1);
    // mesh.texCoord(0, 0);
    // mesh.texCoord(0, 1);
}

// IDEA pass a reference to Graphics& g and plot& p
// use g to do global graphics stuff if needed
// actually draw to p
// then use plot::render(g) to actually draw at the end
// TEX.SUBMIT SHOULD ONLY HAPPEN ONCE PER CYCLE

void plot:: render(al::Graphics& g) {
    g.camera(al::Viewpoint::IDENTITY);  
    al::Color col = al::HSV(1, 1, 1);

    circle(75,75, 30, col);

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

int plot:: get_image_index (int x, int y, al::Image image) {
    return ((y * image.width()) + x) * 4; //stride = 4
}

void plot:: draw_image(int x_position, int y_position, al::Image image) {

    if (image.width() > t_width || image.height() > t_height) {
        std::cout<<"ImAGE TOO BIG!"<<std::endl;;
        return;
    }   

    x_position = x_position + (image.width())/2;
    y_position = y_position + (image.height())/2;

    int position = x_position * t_width + y_position;
    for (int y=image.height()-1;y>=0;y--) {
        for (int x=image.width()-1;x>=0;x--) {

            
            int red = get_image_index(x, y, image);
            int green = red + 1;
            int blue = red + 2;
            int a = red + 3;

            if (a!=0) {
                al::Color c (image.array()[red]/255., image.array()[green]/255., image.array()[blue]/255., image.array()[a]/255.);

                plot_pixel(c, x_position - x, y_position - y);
            }
        }
    }
    // for (int x=image.width(); x>0; x--) {
    //     for (int y=image.height();y>0; y--) {
            
        
    //         int red = get_image_index(x, y, image);
    //         int green = red + 1;
    //         int blue = red + 2;
    //         int a = red + 3;

            // al::Color c (image.array()[idx]/255., image.array()[idx+1]/255., image.array()[idx+2]/255., image.array()[idx+3]/255.);

    //         al::Color c (image.array()[red]/255., image.array()[green]/255., image.array()[blue]/255., image.array()[a]/255.);

    //         plot_pixel(c, x_position + x, y_position + y);
    //     }
    // }
    
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
