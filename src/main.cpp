#include <iostream>
#include <vector>
#include <array>
#include <math.h>

#include "Gamma/SamplePlayer.h"

#include <random>
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

using namespace gam;

using namespace al;
using namespace std;

#define AUDIO_BLOCK_SIZE 128
#define NUMBER_VOICES 12

typedef struct {
  float *values;
  int counter;
  int numblocks;
} meters_t;

struct MyApp : public App {
  SamplePlayer<> samples[NUMBER_VOICES];
  array<float, NUMBER_VOICES> mix_level {0.2, 0.2, 0.2, 0.2, 0.2, 0.4, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2};
  array<Mesh, NUMBER_VOICES> discs;

  Font font;
  Mesh font_mesh;


  void onInit() override {
    navControl().active(false);
    nav().pos(0,0,10);
    samples[0].load("data/count_new.wav");
    samples[1].load("data/beat.wav");
    samples[2].load("data/kick.wav");
    samples[3].load("data/clap.wav");
    samples[4].load("data/perc.wav");

    samples[5].load("data/intro.wav");
    samples[6].load("data/first_half.wav");
    samples[7].load("data/second_half.wav");
    samples[8].load("data/follow_up.wav");
  }
  void onCreate() override {
      for (int i=0;i<NUMBER_VOICES;i++) {
        addDisc(discs[i], 0.5, 30);
        discs[i].color((rand()%100)/20,(rand()%100)/20,(rand()%100)/20);
        discs[i].translate((i%4)-1.5,floor(i/4)-1,0);
        samples[i].pos(samples[i].frames());
      }

      font.load("data/Roboto-Regular.ttf",28,1024);
      font.alignCenter();
      font.write(font_mesh, "hell font", 0.2f);
    }
  
  void onSound(AudioIOData &io) override {
    while(io()){

      float s = 0;
      for (int i=0;i<NUMBER_VOICES;i++) {
        float data = samples[i].read(0);
        samples[i].advance();
        s += data * mix_level[i];
      }
			io.out(0) = io.out(1) = s;
		}
  }

  void onAnimate(double dt) {};

  void onDraw (Graphics &g) {
    g.clear();
    g.blending(true);
    g.blendTrans();

    g.texture();
    font.tex.bind();
    g.draw(font_mesh);
    font.tex.unbind();
    g.meshColor();
    for (int i=0;i<NUMBER_VOICES;i++) {
      // g.color(discs[i].colors());
      g.draw(discs[i]);
    }

    
  }

  bool onKeyDown(Keyboard const &k) override {

    int key_pressed = asciiToIndex(k.key());
    key_pressed -= 30;
    key_pressed = abs(key_pressed) % 12;

    discs[key_pressed].colors().pop_back();
    discs[key_pressed].color((rand()%100)/20,(rand()%100)/20,(rand()%100)/20);
    samples[key_pressed].reset();

    std::cout<<key_pressed<<endl;
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

  // Mesh test;
  // addCube(test, 1.0);
  // test.translate(0,0,2);

  float sr = 44100;
  app.audioDomain()->audioIO().gain(0.5);  // Global output gain.
  app.audioDomain()->configure(sr, AUDIO_BLOCK_SIZE, 4);


  app.start();
  return 0;
}
