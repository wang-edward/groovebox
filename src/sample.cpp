#include "sample.hpp"

//default constructor
sample:: sample() {
    gain = 0.2;
    addDisc(disc, 0.5, 30);
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
void sample:: reset() {
    player.reset();
}
float sample:: output() {
    return player() * gain;
}

// void sample::onProcess(AudioIOData& io) { cout<<"asd"; }

// void sample::onProcess(Graphics& g) { cout<<"asd"; }

// void sample::onTriggerOn() { cout<<"asd"; }

// void sample::onTriggerOff() { cout<<"asd"; }