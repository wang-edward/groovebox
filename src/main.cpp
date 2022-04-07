#include <iostream>
#include <vector>
#include <array>

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
#define NUMBER_VOICES 5

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

class voice {
  private:
    const char* path;
    SamplePlayer<> player;
    float gain;
  public:
    voice(const char* _path, float _gain) {
      load_path(_path);
      gain = _gain;
    }
    void load_path(const char* _path) {
      path = _path;
      player.load(path);
    }
    void gain(float _gain) {
      gain = _gain;
    }
    float output() {
      return player() * gain;
    }
};

struct MyApp : public App {

  SamplePlayer<> player1, player2, player_kick, player_clap, player_perc;

  array<float, NUMBER_VOICES> mix_level {0.2,0.8,0.1,0.1};
  array<float,NUMBER_VOICES> mix;
  array<SamplePlayer<>*, NUMBER_VOICES> players {&player1, &player2, &player_kick, &player_clap, &player_perc};
  void onInit() override {

  }
  void onCreate() override {
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

      float s = 0;
      for (int i=0;i<NUMBER_VOICES;i++) {
        float data = players[i]->read(0);
        players[i]->advance();
        s += data * mix_level[i];
      }
      
      // float s = (player1() + player2() + player_kick() + player_clap() + player_perc()) * 1.0;
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
