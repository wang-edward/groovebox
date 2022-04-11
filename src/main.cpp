#include <iostream>
#include <vector>
#include <array>
#include <filesystem>
#include <string>
#include <random>

#include "Gamma/SamplePlayer.h"
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"
// #include <Player.h>

#include "al/app/al_App.hpp"
// #include "al/sound/al_SoundFile.hpp"
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"
// #include "al/ui/al_FileSelector.hpp"


using namespace gam;

using namespace al;
using namespace std;

#define AUDIO_BLOCK_SIZE 128

enum PLUGIN {PLUGIN_SAMPLER, PLUGIN_SYNTH};

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

#include "sample.hpp"
#include "mpc.hpp"

struct MyApp : public App {
  PLUGIN CURRENT_PLUGIN;
  sample test;
  mpc sampler;

  void onInit() override {
    sampler.init();
  }
  void onCreate() override {
    navControl().active(false);
    nav().pos(0,0,10);
  }
  
  void onSound(AudioIOData &io) override {
    while(io()){
      float s = sampler.output();
			io.out(0) = io.out(1) = s;
		}
  }

  void onDraw (Graphics &g) override {
    sampler.draw(g);
  }

  bool onKeyDown(Keyboard const &k) override {

    int key_pressed = asciiToIndex(k.key());
    key_pressed = key_pressed % 16;
    
    sampler.key_down(key_pressed);

    std::cout<<key_pressed<<endl;
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(Keyboard const& k) override {
  }
    
};

int main() {
  MyApp app;

  // Mesh test;
  // addCube(test, 1.0);
  // test.translate(0,0,2);

  float sr = 44100;
  app.audioDomain()->audioIO().gain(0.5);  // Global output gain.
  app.audioDomain()->configure(sr, AUDIO_BLOCK_SIZE, 4);

  // string path = std::__fs::filesystem::get_current_dir_name();

  app.start();
  return 0;
}
