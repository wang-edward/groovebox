#include "header/plot.hpp"

plot:: plot() {
    //TODO remove?
}

void plot:: init() {

    tex.filterMag(al::Texture::NEAREST); // magnification filter is nearest-neighbour interpolation
    tex.wrap(GL_CLAMP_TO_EDGE); //TODO doesnt work for some reason
    tex.create2D(t_width, t_height, al::Texture::RGBA8, al::Texture::RGBA, al::Texture::UBYTE);

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
// TEX.SUBMIT SHOULD ONLY HAPPEN ONCE PER CYCLE so call at the end of onDraw()

void plot:: render(al::Graphics& g) {
    g.camera(al::Viewpoint::IDENTITY);  
    al::Color col = al::HSV(1, 1, 1);

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

//try to avoid
void plot:: reset_buffer() {
    std::fill(pixels.begin(), pixels.end(), 0);
}