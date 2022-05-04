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
#include "al/graphics/al_Font.hpp"
#include "al/graphics/al_Mesh.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"


#define AUDIO_BLOCK_SIZE 128

enum PLUGIN {PLUGIN_SAMPLER, PLUGIN_SUBTRACTIVE, PLUGIN_WAV_EDITOR};

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

#include "sample.hpp"
#include "mpc.hpp"
#include "SineEnv.hpp"
#include "wav_editor.hpp"
#include "plot.hpp"


struct MyApp : public al::App {
  PLUGIN CURRENT_PLUGIN = PLUGIN_SAMPLER;
  mpc sampler;
  wav_editor editor;
  al::PolySynth pSynth;
  plot screen;

  Image imageData;

  void onInit() override {
    //TODO better config
    dimensions(960,640);
  }
  void onCreate() override { //TODO cleanup
    editor.init();
    sampler.init();
    screen.init();

    const char *filename = "data/image/rectangle.png";
    imageData = Image(filename);

    if (imageData.array().size() == 0) {
      std::cout << "failed to load image" << std::endl;
    }
    std::cout << "loaded image size: " << imageData.width() << ", "
         << imageData.height() << std::endl;

    int temp = 0;
    for (int i : imageData.array()) {
      temp++;
      std::cout<<i<<" ";
      if (temp%4==0) {
        temp = 0; std::cout<<std::endl;
      }
    }


    // screen.draw_image(100,100,imageData);


    // sampler.samples[0].gain = 0.1; //TODO: temporary mix fix
    // pSynth.allocatePolyphony<SineEnv>(16);
    // navControl().active(false);
    // nav().pos(0,0,10);
  }
  
  void onSound(al::AudioIOData &io) override {
    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):      // SAMPLER
          sampler.render(io);
        break;
      case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
        pSynth.render(io);
        break;
    }
  }

  void onDraw (al::Graphics &g) override {
    // g.camera(Viewpoint::UNIT_ORTHO);  
    g.camera(Viewpoint::IDENTITY);  

    g.clear();
    screen.draw_image(75, 75,imageData); 

    screen.render(g); //turns to identity
    // switch (CURRENT_PLUGIN) {
    //   case (PLUGIN_SAMPLER):      // SAMPLER
    //     sampler.draw(g);
    //     break;
    //   case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
    //     pSynth.render(g);
    //     break;
    //   case (PLUGIN_WAV_EDITOR):
    //     editor.render(g);
    //     break;
    // }
  }

  bool onKeyDown(al::Keyboard const &k) override {

    int key_pressed = al::asciiToIndex(k.key());
    std::cout<<key_pressed<<std::endl; // DEBUG

    swap_screens(key_pressed);

    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):      // SAMPLER
        
        if (key_pressed>=20 && key_pressed<mpc::NUMBER_SAMPLES +20) {
          key_pressed = key_pressed - 20;
          sampler.key_down(key_pressed);
        }
        break;
      case (PLUGIN_SUBTRACTIVE):  // SUBTRACTIVE SYNTH
        int midiNote = al::asciiToMIDI(k.key());
        if (midiNote > 0) {
          float frequency = ::pow(2., (midiNote - 69.) / 12.) * 440.;
          SineEnv* voice = pSynth.getVoice<SineEnv>();
          std::cout<<frequency<<std::endl;
          voice->freq(frequency); 
          pSynth.triggerOn(voice, 0, midiNote);
        }

        break;
    }
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    switch (CURRENT_PLUGIN) {
      case (PLUGIN_SAMPLER):
      // TODO: ADD SAMPLER KEYUP
      break;
      case (PLUGIN_SUBTRACTIVE):
        int midiNote = al::asciiToMIDI(k.key());
        if (midiNote > 0) pSynth.triggerOff(midiNote);
      break;
    }
    return true;
  }

  void swap_screens (int key_pressed) {
    if (key_pressed == 0) {
      if (CURRENT_PLUGIN == PLUGIN_SAMPLER) {
        CURRENT_PLUGIN = PLUGIN_SUBTRACTIVE;

      } else {
        CURRENT_PLUGIN = PLUGIN_SAMPLER;
      }
    }
  }
    
};

int main() {
  MyApp app;

  // Start audio
  app.configureAudio(44100., AUDIO_BLOCK_SIZE, 2, 0);

  // Set up sampling rate for Gamma objects
  Domain::master().spu(app.audioIO().framesPerSecond());

  app.start();
}
