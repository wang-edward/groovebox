#ifndef SINE_ENV_HPP
#define SINE_ENV_HPP

#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/io/al_AudioIO.hpp"
#include "al/scene/al_PolySynth.hpp"

// class SineEnv : public al::SynthVoice {
class SineEnv : public al::SynthVoice {
    public:
        float mAmp;
        float mDur;
        gam::Sine<> mOsc;
        gam::Env<3> mAmpEnv;
        al::Mesh mMesh;
        
        SineEnv();

        // Note parameters
        SineEnv& freq(float v);

        // Audio processing function
        void onProcess(al::AudioIOData& io) override;

        // Graphics processing function
        void onProcess(al::Graphics& g) override;

        void onTriggerOn() override;

        void onTriggerOff() override;
};

#endif