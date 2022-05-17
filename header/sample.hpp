#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include "Gamma/SamplePlayer.h"
#include "Gamma/Envelope.h"
#include "al/graphics/al_Shapes.hpp"
#include <iostream>
#include <random>
#include "header/circle.hpp"
#include "header/plot.hpp"

class sample {
  public:
    const char* path;
    gam::SamplePlayer<> player;
    gam::Env<3> amp_envelope;
    float gain;
    al::Color col = al::HSV(0.66,1,1);
    circle disc = circle(100,100, 30, col);


    // void init() override { addDisc(disc, 1.0, 30); }
    
    //constructors
    sample();
    sample (const char* _path, float _gain);
    
    //copy constructor
    sample (const sample &m);

    //copy assignment operator
    sample& operator=(const sample& new_sample);

    //destructor
    ~sample();
    
    // void onProcess(AudioIOData& io) override;

    // void onProcess(Graphics& g) override;

    // void onTriggerOn() override;

    // void onTriggerOff() override;

    void init(const char* _path, float _gain);
    void load_path(const char* _path);
    void update_gain(float _gain);
    void update_envelope(float a, float d, float s, float r);
    void reset_color();
    void trigger_on();
    float output();
};

#endif