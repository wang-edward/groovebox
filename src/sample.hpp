#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include "Gamma/SamplePlayer.h"
#include "al/graphics/al_Shapes.hpp"
#include <iostream>

class sample {
  public:
    const char* path;
    gam::SamplePlayer<> player;
    float gain;
    al::Mesh disc;


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
    void reset();
    float output();
};

#endif