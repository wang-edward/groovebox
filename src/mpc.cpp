#include "header/mpc.hpp"

void mpc:: init() {
    init_files();
    position_discs();
    init_font();
}

void mpc:: init_font() {
    font.load("data/font/Minecraft.ttf", 100, 512);
    font.alignCenter();

    font.write(text, "EHLELLELASDH", 0.2f);
}

void mpc:: init_files() {
    std::string path = "./data/samples";
    int i=0;
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=NUMBER_SAMPLES) {
            break;
        }
        std::string s = file.path();
        // if (s.substr(s.length()-3, s.length()) != ("wav")) {
        //     // i--;
        //     std::cout<<s;
        // }
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
        // samples[i].disc.translate(((i%4)-1.5)/2,(floor(i/4)-1)/2,0); //TODO MAY 17
    }
}

void mpc:: draw(al::Graphics &g) {
    g.clear();

    g.meshColor();
    for (int i=0;i<NUMBER_SAMPLES;i++) {
        // g.draw(samples[i].disc); //TODO MAY 17
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