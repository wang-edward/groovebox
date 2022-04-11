#include <random>


#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"
#include "Gamma/SamplePlayer.h"

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/io/al_AudioIO.hpp"
#include "al/scene/al_PolySynth.hpp"

using namespace gam;
using namespace al;

#define NUMBER_VOICES 16


// Inherit from SynthVoice to determine what each voice should do
// in the onProcess() audio and video callbacks.
// Add functions to set voice parameters (per instance parameters)
// Don't forget to define an onTriggerOn() function to reset envelopes or
// values for each triggering and an onTriggerOff() function to
// determine what the note should do when it is deactivated
class sample_voice : public SynthVoice {
 public:
  sample_voice() {
    // mAmpEnv.curve(0);  // make segments lines
    // mAmpEnv.sustainPoint(2);

    addSphere(mMesh, 0.5, 30, 30);
  }

  // Note parameters
  sample_voice& freq(float v) {
    x = v/5;
    // mOsc.freq(v);
    return *this;
  }

  // Audio processing function
  void onProcess(AudioIOData& io) override {
    while (io()) {
      float s = player();
      io.out(0) += s;
      io.out(1) += s;
    }
  }

  // Graphics processing function
  void onProcess(Graphics& g) override {
    g.pushMatrix();
    g.blending(true);
    g.blendTrans();

    g.translate(x,x,0);
    g.color((rand()%100)/20,(rand()%100)/20,(rand()%100)/20);
    // g.translate(mOsc.freq() / 250 - 3, spatialEnv * 2 - 1, -8);
    // g.color(spatialEnv, mOsc.freq() / 1000, spatialEnv, spatialEnv);
    g.draw(mMesh);
    g.popMatrix();
  }

  void onTriggerOn() override { std::cout<< "hello"<<std::endl;}

  void onTriggerOff() override { std::cout<<"goodbye"<<std::endl; }

 protected:
  float x, y, z;
  Mesh mMesh;
  
};

// We will use PolySynth to handle voice triggering and allocation
struct MyApp : public App {
  PolySynth pSynth;
  SamplePlayer<> players[NUMBER_VOICES];

  void onCreate() override {
    // Pre-allocate voice to avoid real-time allocation
    pSynth.allocatePolyphony<sample_voice>(NUMBER_VOICES);

    navControl().active(false);  // Disable navigation via keyboard, since we
                                 // will be using keyboard for note triggering
    nav().pos(0,0,10);
    for (int i=0;i<16;i++) {

    }
  }

  void onSound(AudioIOData& io) override {
    pSynth.render(io);  // Render audio
  }

  void onDraw(Graphics& g) override {
    g.clear();
    pSynth.render(g);
  }

  bool onKeyDown(Keyboard const& k) override {

    int key = asciiToIndex(k.key());

    key = key % NUMBER_VOICES;

      // float frequency = ::pow(2., (midiNote - 69.) / 12.) * 440.;
      sample_voice* voice = pSynth.getVoice<sample_voice>();
      voice->freq(key);
      pSynth.triggerOn(voice, 0, key);
    
    return true;
  }

  bool onKeyUp(Keyboard const& k) override {
    int key = asciiToIndex(k.key());

    key = key % NUMBER_VOICES;
      pSynth.triggerOff(key);
    
    return true;
  }
};

int main() {
  // Create app instance
  MyApp app;

  // Start audio
  app.configureAudio(44100., 256, 2, 0);

  // Set up sampling rate for Gamma objects
  Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
