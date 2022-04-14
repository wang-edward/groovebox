#include "sample.hpp"

//default constructor
sample:: sample() {
    gain = 0.2;
    addDisc(disc, 0.5, 30);
    disc.color((std::rand()%100)/20,(std::rand()%100)/20,(std::rand()%100)/20);
}

void sample:: init(const char* _path, float _gain) {
    load_path(_path);
    update_gain(_gain);
    player.pos(player.frames());
}
//constructor
sample:: sample (const char* _path, float _gain) {
    load_path(_path);
    gain = _gain;
}
//copy constructor
sample:: sample (const sample &m) {
    path = m.path;
    gain = m.gain;
    load_path(path);
}

sample& sample:: operator=(const sample& new_sample) {

}

sample:: ~sample() {

}

void sample:: load_path(const char* _path) {
    path = _path;
    player.load(path);
    player.pos(player.frames());
}

void sample:: update_gain(float _gain) {
    gain = _gain;
}

void sample:: update_envelope(float a, float d, float s, float r) {
    
}

void sample:: trigger_on() {
    player.reset();


    std::cout<<"ONE"<<disc.colors().size()<<std::endl;
    disc.colors().pop_back();


    std::cout<<"TWO"<<disc.colors().size()<<std::endl;
    disc.color((std::rand()%100)/20,(std::rand()%100)/20,(std::rand()%100)/20);

    std::cout<<"Three"<<disc.colors().size()<<std::endl;
}

float sample:: output() {
    return player() * gain;
}

// void sample::onProcess(AudioIOData& io) { cout<<"asd"; }

// void sample::onProcess(Graphics& g) { cout<<"asd"; }

// void sample::onTriggerOn() { cout<<"asd"; }

// void sample::onTriggerOff() { cout<<"asd"; }