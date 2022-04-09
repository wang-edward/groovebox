#include <iostream>
#include <vector>
#include <array>

#include "Gamma/SamplePlayer.h"
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"
// #include <Player.h>

#include "al/app/al_App.hpp"
// #include "al/sound/al_SoundFile.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"

using namespace gam;

using namespace al;
using namespace std;

#define AUDIO_BLOCK_SIZE 128
#define NUMBER_VOICES 5

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

#include "sample.hpp"

struct MyApp : public App {
  sample voices[NUMBER_VOICES];
  void onInit() override {
    
  }
  void onCreate() override {
    sample test("data/beat.wav", 0.2);
    sample *new_test = new sample("data/beat.wav", 0.2);
    // voices[0] = *new_test;

  }
  
  void onSound(AudioIOData &io) override {
    while(io()){
      float s = 0;
      for (int i=0;i<NUMBER_VOICES;i++) {
      }
			io.out(0) = io.out(1) = s;
		}
  }

  bool onKeyDown(Keyboard const &k) override {
    std::cout<<"start"<<endl;


    int key_pressed = asciiToIndex(k.key());
    switch(key_pressed) {
      case 30:
        // player1.reset();
        break;
      case 31:
        // player2.reset();
        break;
      case 32:
        // player_kick.reset();
        break;
      case 33:
        // player_clap.reset();
        break;
      case 34:
        // player_perc.reset();
        break; 
    }
    std::cout<<"end"<<endl;
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(Keyboard const& k) override {
  }
    
};

int main() {
  MyApp app;

  float sr = 44100;
  app.audioDomain()->audioIO().gain(0.5);  // Global output gain.
  app.audioDomain()->configure(sr, AUDIO_BLOCK_SIZE, 4);


  app.start();
  return 0;
}
