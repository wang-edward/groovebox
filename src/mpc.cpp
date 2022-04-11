#include "mpc.hpp"

void mpc:: init() {
    init_files();
    position_discs();
    color_discs();
}

void mpc:: init_files() {
    std::string path = "./data";
    int i=0;
    for (const auto& file : std::__fs::filesystem::directory_iterator(path)) {
        if (i>=16) {
            break;
        }
        std::string s = file.path();
        samples[i].load_path(s.c_str()); //convert string to const char*
        std::cout<< s.substr(2,s.length())<<std::endl; //skip "./" in file path
        i++;
    }
}

void mpc:: position_discs() {
    for (int i=0;i<NUMBER_VOICES;i++) {
        samples[i].disc.translate((i%4)-1.5,floor(i/4)-1,1);
    }
}

void mpc:: color_discs() {

    for (int i=0;i<NUMBER_VOICES;i++) {
        samples[i].disc.color((rand()%100)/20,(rand()%100)/20,(rand()%100)/20);
    }
}

void mpc:: draw(al::Graphics &g) {
    g.meshColor();
    for (int i=0;i<NUMBER_VOICES;i++) {
        g.draw(samples[i].disc);
    }
}

float mpc:: output() {
    float s = 0;
    for (int i=0;i<NUMBER_VOICES;i++) {
        s += samples[i].output();
        // std::cout<<sampler.samles[i]
      }
    return s;
}

void mpc:: key_down(int key) {
    samples[key].reset();
}