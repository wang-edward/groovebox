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

#include "al/app/al_App.hpp"
// #include "al/sound/al_SoundFile.hpp"
#include "al/sound/al_Speaker.hpp"

#include "Gamma/SamplePlayer.h"
using namespace gam;

using namespace al;
using namespace std;

#define AUDIO_BLOCK_SIZE 512

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public App {

  SamplePlayer<> player1, player2;

  float mix_level[4];

  void onInit() {
      player1.load("data/count_new.wav");

      // Assign player1's buffer to player2;
      // this can be called safely in the audio thread.
      player2.buffer(player1);

      // Make second playback rate slightly higher to create "phasing"
      player2.rate(2.0);
    }
  
  void onSound(AudioIOData &io) override {
    while(io()){
			float s = (player1() + player2()) * 0.5;
			player1.loop();
			player2.loop();
			io.out(0) = io.out(1) = s;
		}
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
