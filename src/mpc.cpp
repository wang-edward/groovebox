#include "mpc.hpp"

void mpc:: init() {
    init_files();
    position_discs();
    init_font();
}

void mpc:: init_font() {
    font.load("data/Roboto-Regular.ttf", 28, 1024);
    font.alignCenter();

    font.write(text, "EHLELLELASDH", 0.2f);
}

void mpc:: init_files() {
    std::string path = "./data";
    int i=0;
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=NUMBER_SAMPLES) {
            break;
        }
        std::string s = file.path();
        samples[i].load_path(s.c_str()); //convert string to const char*
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
        i++;
    }
}

void mpc:: color_discs() {
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        samples[i].reset_color();
    }
}

void mpc:: position_discs() {
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        samples[i].disc.translate((i%4)-1.5,floor(i/4)-1,1);
    }
}

void mpc:: draw(al::Graphics &g) {
    g.clear();

    g.meshColor();
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        g.draw(samples[i].disc);
    }
    
    draw_gui(g);
}

void mpc:: draw_gui(al::Graphics &g) {
    g.blending(true);
    g.blendTrans();
    g.texture();
    font.tex.bind();
    g.draw(text);
    font.tex.unbind();
    g.blending(false);
}

void mpc:: render(al::AudioIOData &io) {
    while(io()){
        float s = 0;
        for (int i=0;i<NUMBER_SAMPLES;i++) {
            s += samples[i].output();
        }
        io.out(0) = io.out(1) = s;
    }
}

void mpc:: key_down(int key) {
    samples[key].trigger_on();
}