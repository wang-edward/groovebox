/*
What is our "Hello world!" app?

An agent orbits around the origin emitting the audio line input. The camera
view can be switched between a freely navigable keyboard/mouse controlled mode
and a sphere follow mode.

Requirements:
2 channels of spatial sound
2 windows, one front view, one back view
stereographic rendering
*/

#include <iostream>
#include <vector>

#include "Gamma/SamplePlayer.h"

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

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public App {

  SamplePlayer<> player1, player2, player_kick, player_clap, player_perc;

  float mix_level[4];

  void onInit() {
      player1.load("data/count_new.wav");
      player2.load("data/beat.wav");
      player_kick.load("data/kick.wav"); 
      player_clap.load("data/clap.wav"); 
      player_perc.load("data/perc.wav");

      // Assign player1's buffer to player2;
      // this can be called safely in the audio thread.
      // player2.buffer(player1);

      // Make second playback rate slightly higher to create "phasing"
      // player2.rate(1.0);
      player1.pos(player2.frames());
      player2.pos(player2.frames());
      player_kick.pos(player_kick.frames());
      player_clap.pos(player_clap.frames());
      player_perc.pos(player_perc.frames());

    }
  
  void onSound(AudioIOData &io) override {
    while(io()){
			// float s = (player1() + player2()) * 0.5;
      float s = (player1() + player2() + player_kick() + player_clap() + player_perc()) * 0.2;
			// player1.loop();
			// player2.loop();
      // player1.finish(); player2.finish();
			io.out(0) = io.out(1) = s;
		}
  }

  bool onKeyDown(Keyboard const &k) override {
    std::cout<<"start"<<endl;


    int key_pressed = asciiToIndex(k.key());
    switch(key_pressed) {
      case 30:
        player1.reset();
        break;
      case 31:
        player2.reset();
        break;
      case 32:
        player_kick.reset();
        break;
      case 33:
        player_clap.reset();
        break;
      case 34:
        player_perc.reset();
        break; 
    }
    std::cout<<"end"<<endl;
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(Keyboard const& k) override {
    int midiNote = asciiToMIDI(k.key());
    if (midiNote > 0) {
    }
    return true;
  }
    
};

int main() {
  std::vector<std::string> filenames;
  filenames.push_back("data/count_new.wav");
  filenames.push_back("data/count.wav");
  filenames.push_back("data/count.wav");
  filenames.push_back("data/count.wav");

  MyApp app;

  float sr = 44100;
  app.audioDomain()->audioIO().gain(0.5);  // Global output gain.
  app.audioDomain()->configure(sr, AUDIO_BLOCK_SIZE, 4);


  app.start();
  return 0;
}
